#include <iostream>
#include "insertion.h"
#include "shellsort.h"
#include "heapsort.h" 
#include "mergesort.h"
#include "quicksort.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void printNum(vector<int>& nums)
{
	for(auto n : nums)
		cout<<n<<" ";
	cout<<endl;
}


int main(int argc, char** argv) {
	vector<int> nums = {1,4,2,78,24,5,8,6,100};
	//InsertionSort(nums);
	//ShellSort(nums);
	
	//heapSort(nums);
	//mergeSort(nums);
	quickSort(nums);
	printNum(nums);
	return 0;
}
