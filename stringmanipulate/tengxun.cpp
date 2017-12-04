#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map> 


using namespace std;
 
// 1 2 3 29 30 31
//  1 1 26 1  1
 
void findNumOfMaxPair(vector<int> nums) {
    sort(nums.begin(), nums.end());
    int maxVal = 0;
    int front = 0;
    int rear = nums.size() - 1;
    int a = 0, b = 0;
    while(front < rear) {
        int tmp = nums[rear] - nums[front];
        if(tmp >= maxVal) {
            maxVal = tmp;
            a++;
            front++;
        }
        if(tmp < maxVal)
            break;
    }
    front = 0;
    while(front < rear) {
        int tmp = nums[rear] - nums[front];
        if(tmp >= maxVal) {
            maxVal = tmp;
            b++;
            rear--;
        }
        if(tmp < maxVal)
            break;
    }
     
    cout<<" "<<a*b<<endl;
}
 
void findNumOfMinPair(vector<int> nums) {
    sort(nums.begin(), nums.end());
    int minVal = 100000;
    for(int i = 1; i < nums.size(); i++) {
    	cout<<"num:"<<nums[i]<<endl;
        int tmp = nums[i] - nums[i-1];
        cout<<"tmp:"<<tmp<<endl;
		if(tmp < minVal)
            minVal = tmp;
    }
    
    unordered_map<int, int> numsMap;
    
    for(auto num : nums) {
        if(numsMap.find(num) != numsMap.end()) {
            numsMap[num]++;
        }
        else {
            numsMap.emplace(num, 1);
        }
    }
    
    int minPairNum = 0;
    
    if(minVal == 0) {
        for(auto it = numsMap.begin(); it != numsMap.end(); it++) {
            if(it->second > 1) {
                minPairNum = minPairNum + (it->second * (it->second - 1))/2;
            }
        }
    }
    else {
        for(int i = 0; i < nums.size(); i++) {
            if(numsMap.find(nums[i] + minVal) != numsMap.end()) {
                minPairNum++;
            }
        }
    }
    cout<<minVal<<endl; 
    cout<<minPairNum;
}
 
int main(void) {
    int num = 0;
    int lineno = 1;
     
    while(cin>>num) {
        vector<int> nums;
        for(int i = 0; i < num; i++) {
            int tmp = 0;
            cin>>tmp;
            nums.push_back(tmp);
        }
        findNumOfMinPair(nums);
        findNumOfMaxPair(nums);
    }
     
    return 0;
     
}
