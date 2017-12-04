#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void solution(vector<int> nums, int length)
{
     if(length == 0) return;

     //find the min and max value and store elements into map, the key is the number, the value is the times it appears
     
     int maxVal = nums[0];
     int minVal = nums[0];
     unordered_map<int, int> numsMap;
     unordered_map<int, int>::const_iterator got;
     for(int i = 0; i < length; i++) {
          if(nums[i] > maxVal)
                maxVal = nums[i];
          if(nums[i] < minVal)
                minVal = nums[i];
          got = numsMap.find(nums[i]);
          
          //if cannot find same num in map, then emplace it
          
          if(got == numsMap.end()) 
                numsMap.emplace(nums[i], 1);
          else 
                numsMap[nums[i] ]++;
     }
     cout<<"Range is "<<minVal<<"to "<<maxVal<<endl;


     //find missing number
     cout<<"Missing numbers:"<<endl;
     for(int i = minVal + 1; i < maxVal; i++) {
          got = numsMap.find(i);
          if(got == numsMap.end())
                cout<<i<<endl;
     }


     //find the duplicate numbers
     cout<<"Duplicate numbers:"<<endl;
     for(unordered_map<int, int>::iterator it = numsMap.begin(); it != numsMap.end(); it++) {
          if(it->second > 1)
               cout<<it->first<<" appears "<<it->second<<" times."<<endl;
     }
} 


int main(void)
{
	vector<int> nums = {1,1,1,2,2,-4,-8,10000,-10000,34,56,778,77};
	solution(nums, nums.size());
	return 0;
}


