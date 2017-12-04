#include "filter.h"


void filter::printSource(vector<string> s)
{
	for(auto str:s)
		cout<<str<<endl;
}

void filter::printLine(string &s)
{
	if(s.size()==0) return;
	vector<string> source = splitString(s, "|");
	vector<string> sourceCpy = source;
	for(auto &str : source) {
		lowercase(str);
		cout<<"low";
		deleteExtra(str);
		cout<<"dele";
		deleteWhiteSpace(str);
	}
	printSource(source);
	vector<int> filterOut;
	unordered_set<int> posSet;
	unordered_set<int>::const_iterator got;
	for(int i = 0; i < source.size(); i++) {
		got = posSet.find(i);
		if(got != posSet.end()) continue;
		for(int j = i + 1; j < source.size(); j++) {
			got = posSet.find(j);
			if(got != posSet.end()) continue;			

			//source[i] == source[j]
			if(source[i].compare(source[j])== 0) {
				if(sourceCpy[i].size() > sourceCpy[j].size()) {
					posSet.emplace(i);
					break;
				}
				else {
					posSet.emplace(j);
					continue;
				}
			}

			
			bool contain = false;
			contain = contains(source[j], source[i]);
			if(contain == true) {
				posSet.emplace(i);
				break;
			}
			contain = false;
			contain = contains(source[i], source[j]);
			if(contain == true) {
				posSet.emplace(j);
			}
		}
	}
	int cnt = 0;
	for(int i = 0; i < sourceCpy.size(); i++) {
		got = posSet.find(i);
		if(got == posSet.end()) {
			cout<<sourceCpy[i];
			cnt++;
			if(cnt < source.size()-posSet.size())
				cout<<"|";
		}
	}
	cout<<endl;
}
vector<string> filter::splitString(const string &s, const string &seperator)
{
	vector<string> res;
	size_t pos1, pos2;
	pos1 = 0;
	pos2 = s.find(seperator);
	while(pos2 != string::npos)
	{
		res.push_back(s.substr(pos1, pos2-pos1));
		pos1 = pos2 + seperator.size();
		pos2 = s.find(seperator, pos1);
	}
	if(pos1 != s.length())
		res.push_back(s.substr(pos1));
	return res;

}
void filter::lowercase(string &s)
{
	for(int i = 0; i < s.length(); i++) {
		if(s[i] >= 'A' && s[i] <= 'Z')
			s[i] = s[i] + 32;
	}
}

void filter::deleteExtra(string &s)
{
	vector<int> pos;
	for(int i = 0; i < s.length(); i++) {
		if((s[i] < 'a' || s[i] > 'z') && s[i] != ' ' ) {
			if(s[i] < '0' || s[i] > '9')
				pos.push_back(i);
		}
	}
	for(int i = 0; i < pos.size(); i++) {
		s.erase(pos[i]-i, 1);
	}
}
void filter::deleteWhiteSpace(string &s)
{
	if(!s.empty()) {
		s.erase(0, s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);
	}

	size_t index = 0;
	if(!s.empty()) {
		while((index = s.find(" ", index)) != string::npos) {
			if(s[index - 1] == ' ')
				s.erase(index, 1);
			else
				index++;
		}
	}
}

// s1 contains s2 ?
bool filter::contains(const string &s1, const string &s2)
{
	if(s1.length() < s2.length())
		return false;
	size_t pos = s1.find(s2, 0);
	if(pos != string::npos)
		return true;
	return false;
	
	
	/*//cout<<"s2:"<<s1<<endl;

	unordered_map<string, int> strMap;
	vector<string> substr_1;
	substr_1 = splitString(s1, " ");
	//cout<<substr_1.size()<<endl;
	vector<string> substr_2;
	substr_2 = splitString(s2, " ");
	//cout<<substr_2.size()<<endl;
	for(int i = 0; i < substr_1.size(); i++) {
		strMap.emplace(substr_1[i], i);
	}
	int lastFind = -1;
	
	for(auto s : substr_2) {
		//cout<<"sub2 "<<s<<endl;
		unordered_map<string, int>::const_iterator got = strMap.find(s);
		if(got == strMap.end())
			return false;
		else {
			int index = strMap[s];
			if(index <= lastFind)
				return false;
			lastFind = index;
		}
	}
	return true;*/
}
