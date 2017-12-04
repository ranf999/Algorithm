// huawei.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>

using namespace std;




vector<string> splitString(const string &s, const string &seperator)
{
	vector<string> v;
	size_t pos1, pos2;
	pos1 = 0;
	pos2 = s.find(seperator, pos1);
	while (string::npos != pos2) {
		v.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + seperator.size();
		pos2 = s.find(seperator, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
	return v;
}

bool parse(vector<vector<int> > &matrix) {
	bool hasChanged = false;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
			int cnt = 0;
			if (matrix[i][j] == 0) {
				if (i - 1 >= 0 && matrix[i - 1][j] == 1) cnt++;
				if (i + 1 < matrix.size() && matrix[i + 1][j] == 1) cnt++;
				if (j - 1 >= 0 && matrix[i][j - 1] == 1) cnt++;
				if (j + 1 < matrix[0].size() && matrix[i][j + 1] == 1) cnt++;
				if (cnt >= 2) {
					matrix[i][j] = 1;
					hasChanged = true;
				}
			}
		}
	}
	return hasChanged;
}


int main()
{
	ifstream ifs;
	vector<string> nums;
	string tmp;
	ifs.open("PracticeInput.txt", std::ifstream::in);
	while (ifs >> tmp) {
		nums.push_back(tmp);
	}

	

	system("PAUSE");
	return 0;
}

