#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_
#include "global.h"
#include "heap.h"

void qSort(vector<int>& A,int left,int right);
int median3(vector<int>& A, int left, int right);

void quickSort(vector<int>& A)
{
	int n = A.size();
	if(n == 0) return;
	qSort(A,0,n-1);
}

void qSort(vector<int>& A,int left,int right)
{

	if(left <= right - 3)
	{
		int pivot = median3(A,left,right);
		int i = left; 
		int j = right - 2;
		while(1)
		{
			while(A[i] < pivot) i++;
			while(A[j] > pivot) j--;
			if(i < j)
				swap(A[i],A[j]);
			else
				break;
		}
		swap(A[i],A[right-1]);
		qSort(A,left,i-1);
		qSort(A,i+1,right);
		//qSort(A,left,center);
	}
	else
	{
		if(left == right) return;
		int center = (left+right)/2;	
		if(A[left] > A[center])
			swap(A[left], A[center]);
		if(A[left] > A[right])
			swap(A[left], A[right]);
		if(A[center] > A[right])
			swap(A[center],A[right]);
	}
}

int median3(vector<int>& A, int left, int right)
{
	int center = (left+right)/2;
	if(A[left] > A[center])
		swap(A[left], A[center]);
	if(A[left] > A[right])
		swap(A[left], A[right]);
	if(A[center] > A[right])
		swap(A[center],A[right]);
	swap(A[center], A[right-1]);
	return A[right-1];
}
#endif
