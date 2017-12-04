#ifndef _HEAP_H_
#define _HEAP_H_
#include <iostream>
#include <vector>

using namespace std;

class Heap
{
private:
	vector<int> heap;
	void percolateDown(vector<int>& nums, int i);
public:
	Heap(){}
	Heap(vector<int> nums);
	void heapify(vector<int>& nums);
	int top();
	void pop();
	void push(int num);
	void display();
	int size();
	bool isEmpty();
};

Heap::Heap(vector<int> nums)
{
    int n = nums.size();
	for(int i = n/2; i > 0; i--)
	 	percolateDown(nums,i);	
	this->heap = nums;
}

bool Heap::isEmpty()
{ 
	if(heap.size() == 0)
		return true;
	return false;
} 

int Heap::size()
{ 
	return heap.size();
}

void Heap::push(int num)
{ 
	heap.push_back(num);
	int n = heap.size();
	int tmp = num;
	int i = 0;
	for(i = n; i/2 >= 1 && num < heap[i/2-1]; i /= 2)
		heap[i-1] = heap[i/2-1];
	heap[i-1] = tmp;
}

void Heap::heapify(vector<int>& nums)
{
    int n = nums.size();
	for(int i = n/2; i > 0; i--)
	 	percolateDown(nums,i);	
}

void Heap::percolateDown(vector<int>& nums, int i)
{
	//parent, left, right
	int n = nums.size();
	int parent = i;
	int left = i * 2;
	int right = i * 2 + 1;
   	if(left <= n && nums[parent - 1] > nums[left - 1])
		parent = left;
	if(right <= n && nums[parent - 1] > nums[right - 1])
		parent = right;
	if(parent != i)
		swap(nums[parent-1],nums[i-1]);
	else
		return;
	percolateDown(nums, parent);
}

void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

int Heap::top()
{
	return heap[0];
} 

void Heap::pop()
{ 
	if(heap.size()==0) return;
	int n = heap.size();
	heap[0] = heap[n-1];
	heap.pop_back();
	percolateDown(heap,1);
}

void Heap::display()
{
	for(auto n : heap)
		cout<<n<<" ";
	cout << endl;
}
#endif
