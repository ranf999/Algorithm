#include<iostream>
#include <vector>

using namespace std;


int binarySearch(vector<int>& nums, int l, int r, int target) {
	if(l <= r) {
		int mid = l + (r - l)/2;
		if(nums[mid] == target) {
			return mid;
		}
		if(nums[mid] > target) {
			return binarySearch(nums, l, mid-1, target);
		}
		return binarySearch(nums, mid+1, r, target);
	} 
	return -1;
}

int binarySearch_1(vector<int>& nums, int target) {
	int l = 0;
	int r = nums.size() - 1;
	
	
	while(l <= r) {
		int mid = l + (r - l)/2;
		if(nums[mid] == target) return mid;
		if(nums[mid] > target) r = mid - 1;
		if(nums[mid] < target) l = mid + 1;
	}
	
	return -1;
}



int main(void) {
	vector<int> nums = {1,3,4,5,6,7,8,13,53,67,89};
	//cout <<  binarySearch(nums,0,nums.size()-1, 8) <<endl;
	cout << binarySearch_1(nums, 8) << endl;
	return 0; 
} 
