#include "heap.h"
#include "global.h"

void heapSort(vector<int>& nums)
{
	Heap *heap = new Heap(nums);
	heap->display();
	int n  =  nums.size();
	for(int i = 0; i < n; i++)
	{
		nums[i] = heap->top();
		
		heap->pop();
		heap->display();
	}
}
