#include <iostream>
#include "heap.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	vector<int> nums = {7,2,6,8,1,5,3,2};
	Heap heap;
	for(auto n : nums)
		heap.push(n);
	heap.display();
	Heap *heap2 = new Heap(nums);
	heap2->pop();
	heap2->display();
	return 0;
}
