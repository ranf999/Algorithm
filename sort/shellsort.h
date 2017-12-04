#include "global.h"

void ShellSort(vector<int>& nums)
{
	int n = nums.size();
	int increment = 0;
	int tmp = 0;
	int j = 0;
	for(increment = n/2; increment > 0; increment /= 2)
		for(int i = increment; i < n; i++)
		{
			tmp = nums[i];
			for(j = i; j-increment >= 0 && tmp < nums[j - increment]; j -= increment)
				nums[j] = nums[j - increment];
			nums[j] = tmp;
		}
}
