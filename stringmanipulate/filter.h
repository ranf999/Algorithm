#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class filter
{
public:
	vector<string> splitString(const string &s, const string &seperator);
	void lowercase(string &s);
	void deleteExtra(string &s);
	void deleteWhiteSpace(string &s);
	bool contains(const string &s1, const string &s2);
	//vector<string> splitString(const string &s, const string &seperator);
	void printLine(string &s);
	void printSource(vector<string> s);
};
