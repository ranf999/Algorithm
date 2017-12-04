#ifndef _INSERTION_H_
#define _INSERTION_H_
#include "global.h"

void InsertionSort(vector<int>& nums)
{
	int n = nums.size();
	if(n==0||n==1) return;
	int tmp = 0;
	int i = 0;
	for(int p = 1; p < n; p++)
	{
		tmp = nums[p];
		for(i = p; i >= 0 && nums[i-1] > tmp; i--)
			nums[i] = nums[i-1];
		nums[i] = tmp;
	}
}
#endif
