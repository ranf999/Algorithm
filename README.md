```c
	#include "config.h"
	#include "globals.h"
	
	#include "errno.h"
	
	#include "util/init.h"
	#include "util/debug.h"
	#include "util/list.h"
	#include "util/string.h"
	
	#include "proc/kthread.h"
	#include "proc/proc.h"
	#include "proc/sched.h"
	
	#include "mm/slab.h"
	#include "mm/page.h"
	
	kthread_t *curthr; /* global */
	static slab_allocator_t *kthread_allocator = NULL;
	
	#ifdef __MTP__
	/* Stuff for the reaper daemon, which cleans up dead detached threads */
	static proc_t *reapd = NULL;
	static kthread_t *reapd_thr = NULL;
	static ktqueue_t reapd_waitq;
	static list_t kthread_reapd_deadlist; /* Threads to be cleaned */
	
	static void *kthread_reapd_run(int arg1, void *arg2);
	#endif
	
	void
	kthread_init()
	{
	        kthread_allocator = slab_allocator_create("kthread", sizeof(kthread_t));
	        KASSERT(NULL != kthread_allocator);
	}
	
	/**
	 * Allocates a new kernel stack.
	 *
	 * @return a newly allocated stack, or NULL if there is not enough
	 * memory available
	 */
	static char *
	alloc_stack(void)
	{
	        /* extra page for "magic" data */
	        char *kstack;
	        int npages = 1 + (DEFAULT_STACK_SIZE >> PAGE_SHIFT);
	        kstack = (char *)page_alloc_n(npages);
	
	        return kstack;
	}
	
	/**
	 * Frees a stack allocated with alloc_stack.
	 *
	 * @param stack the stack to free
	 */
	static void
	free_stack(char *stack)
	{
	        page_free_n(stack, 1 + (DEFAULT_STACK_SIZE >> PAGE_SHIFT));
	}
	
	void
	kthread_destroy(kthread_t *t)
	{
	        KASSERT(t && t->kt_kstack);
	        free_stack(t->kt_kstack);
	        if (list_link_is_linked(&t->kt_plink))
	                list_remove(&t->kt_plink);
	
	        slab_obj_free(kthread_allocator, t);
	}
	
	/*
	 * Allocate a new stack with the alloc_stack function. The size of the
	 * stack is DEFAULT_STACK_SIZE.
	 *
	 * Don't forget to initialize the thread context with the
	 * context_setup function. The context should have the same pagetable
	 * pointer as the process.
	 */
	kthread_t *
	kthread_create(struct proc *p, kthread_func_t func, long arg1, void *arg2)
	{
			
			KASSERT(NULL != p); /* should have associated process */
			
	
			/* Create a kthread_t object in heap */
			kthread_t* thr = (kthread_t*) slab_obj_alloc(kthread_allocator);
			
			/* Init stack of the new thread */
			thr->kt_kstack = alloc_stack();
	
			/* Setup thread context */
			context_setup(&thr->kt_ctx, func, arg1, arg2, 
					thr->kt_kstack, DEFAULT_STACK_SIZE, p->p_pagedir);
	
			thr->kt_retval = 0;
			thr->kt_errno = 0;
			thr->kt_proc = p;
			thr->kt_cancelled = 0;
			thr->kt_wchan = NULL;
			thr->kt_state = KT_NO_STATE;
			list_link_init(&thr->kt_plink);
			list_link_init(&thr->kt_qlink);
	
			/* Set kt_plink of new thr */
			list_insert_head(&p->p_threads, &thr->kt_plink);
	
	        return thr;
	}
	
	/*
	 * If the thread to be cancelled is the current thread, this is
	 * equivalent to calling kthread_exit. Otherwise, the thread is
	 * sleeping and we need to set the cancelled and retval fields of the
	 * thread.
	 *
	 * If the thread's sleep is cancellable, cancelling the thread should
	 * wake it up from sleep.
	 *
	 * If the thread's sleep is not cancellable, we do nothing else here.
	 */
	void
	kthread_cancel(kthread_t *kthr, void *retval)
	{
			
			KASSERT(NULL != kthr); /* should have thread */
			
	
			/* the following lines are not exercised by kernel 1 tests but should be there */
			/*if(kthr == curthr) {*/
				/*kthread_exit(retval);*/
				/*return;*/
			/*}*/
	
			curthr->kt_retval = retval;
			/*set kt_cancelled=1 and remove from sleep queue and add to run queue if cancellable */
			sched_cancel(kthr);
	}
	
	/*
	 * You need to set the thread's retval field, set its state to
	 * KT_EXITED, and alert the current process that a thread is exiting
	 * via proc_thread_exited.
	 *
	 * It may seem unneccessary to push the work of cleaning up the thread
	 * over to the process. However, if you implement MTP, a thread
	 * exiting does not necessarily mean that the process needs to be
	 * cleaned up.
	 */
	void
	kthread_exit(void *retval)
	{
			
			curthr->kt_retval = retval;
			curthr->kt_state = KT_EXITED;
	
			/* curthr should not be in any queue */
			KASSERT(!curthr->kt_wchan); 
			
			/* queue should be empty */
			KASSERT(!curthr->kt_qlink.l_next && !curthr->kt_qlink.l_prev); 
			
			/* current exiting thread is the in the current process */
			KASSERT(curthr->kt_proc == curproc);
			
	
			proc_thread_exited(retval);	/*everything clean up by proc */
	}
	
	/*
	 * The new thread will need its own context and stack. Think carefully
	 * about which fields should be copied and which fields should be
	 * freshly initialized.
	 *
	 * You do not need to worry about this until VM.
	 */
	kthread_t *
	kthread_clone(kthread_t *thr)
	{
			kthread_t* clone = (kthread_t*) slab_obj_alloc(kthread_allocator);
			clone->kt_kstack = alloc_stack();
			/* Init other fields */
			clone->kt_retval = 0;
			clone->kt_cancelled = 0;
			clone->kt_wchan = NULL;
			clone->kt_state = KT_NO_STATE;
			list_link_init(&clone->kt_plink);
			list_link_init(&clone->kt_qlink);
	        
	        return clone;
	}
	
	/*
	 * The following functions will be useful if you choose to implement
	 * multiple kernel threads per process. This is strongly discouraged
	 * unless your weenix is perfect.
	 */
	#ifdef __MTP__
	int
	kthread_detach(kthread_t *kthr)
	{
	        NOT_YET_IMPLEMENTED("MTP: kthread_detach");
	        return 0;
	}
	
	int
	kthread_join(kthread_t *kthr, void **retval)
	{
	        NOT_YET_IMPLEMENTED("MTP: kthread_join");
	        return 0;
	}
	
	/* ------------------------------------------------------------------ */
	/* -------------------------- REAPER DAEMON ------------------------- */
	/* ------------------------------------------------------------------ */
	static __attribute__((unused)) void
	kthread_reapd_init()
	{
	        NOT_YET_IMPLEMENTED("MTP: kthread_reapd_init");
	}
	init_func(kthread_reapd_init);
	init_depends(sched_init);
	
	void
	kthread_reapd_shutdown()
	{
	        NOT_YET_IMPLEMENTED("MTP: kthread_reapd_shutdown");
	}
	
	static void *
	kthread_reapd_run(int arg1, void *arg2)
	{
	        NOT_YET_IMPLEMENTED("MTP: kthread_reapd_run");
	        return (void *) 0;
	}
```	
