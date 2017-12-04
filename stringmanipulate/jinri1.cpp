#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main(void)
{
	int num;
	cin >> num;
	vector<int> nums(num);
	for(int i = 0; i < num; i++) {
		cin >> nums[i];
	}
	stack<int> increase;
	stack<int> decrease;
	int maxLen = -1;
	int start = 0;
	int end = 0;
	for(int i = 0; i < num; i++) {
		bool isSeq = true;
		bool isIncre = true; 
		int j = 0;
		for(j = i; j < num; j++) {
			//increase
			if(!isSeq) break;
			if(increase.empty() && isSeq && isIncre) {
				increase.push(nums[j]);
				continue;
			}
			else if(increase.top() < nums[j] && isSeq && isIncre){
				increase.push(nums[j]);
				continue;
			}
			else if(increase.top() > nums[j] && isSeq) {
				//decrease
				isIncre = false;
				if(decrease.empty() && isSeq) {
					decrease.push(nums[j]);
					//end = j;
					continue;
				}
				else if(decrease.top() > nums[j] && isSeq) {
					decrease.push(nums[j]);
					//end = j;
					continue;
				}
			}
			
			isSeq = false;
		}
		
		int len = -1;
		if((increase.size() > 1) && !decrease.empty()) {
			len = increase.size() + decrease.size();
			if(len > maxLen) {
				maxLen = len;
				start = i;
				end = j - 2;
			}
				
		}
		while(!increase.empty())
			increase.pop();
		while(!decrease.empty())
			decrease.pop();
		
	}
	if(maxLen != -1)
	cout << start <<" "<< end <<endl;
	else
	cout<<-1<<endl;
	return 0;
} 
