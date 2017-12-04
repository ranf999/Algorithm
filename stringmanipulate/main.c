#include "ancester.h"
#include "Outthink.h"
#include "filter.h"


vector<int> splitNum(string input, string seperator)
{
	vector<int> nums;
	size_t pos1, pos2;
	pos1 = 0;
	cout<<"asfgda"<<seperator<<"gagag"<<endl;
	pos2 = input.find(seperator, pos1);
	while(pos2 != string::npos) {
		nums.push_back(atoi(input.substr(pos1, pos2-pos1).c_str()));
		pos1 = pos2 + seperator.size();
		pos2 = input.find(seperator, pos1);
	}
	if(pos1 != input.length()) {
		nums.push_back(atoi(input.substr(pos1, pos2-pos1).c_str()));
	}
	return nums;
}


int main(void) 
{ 
	string input;
	getline(cin, input);
	//cout<<input<<endl;
	filter filter;
	filter.printLine(input);


	//string a = " ";
	//vector<int> nums = splitNum(input, a);
	//solution1 solution;
	//solution.printLine(nums[0], nums[1], nums[2]);

	//cin>>input;
	//solution solution;
    //string res = solution.getNearestCommonAncester(input);
	//cout<<res<<endl;
	return 0;
}
