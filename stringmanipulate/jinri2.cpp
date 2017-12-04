#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

vector<string> splitString(string &s, const string &seperator)
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
void lowercase(string &s)
{
	for(int i = 0; i < s.length(); i++) {
		if(s[i] >= 'A' && s[i] <= 'Z')
			s[i] = s[i] + 32;
	}
}



int main(void) {
	int N, M;
	string input;
	getline(cin, input);
	vector<string> num = splitString(input," ");
	N = atoi(num[0].c_str());
	M = atoi(num[1].c_str());
	vector<string> para;
	vector<string> query;
	for(int i = 0; i < N; i++) {
		getline(cin, input);
		lowercase(input);
		para.push_back(input);
		
	}
	for(int i = 0; i < M; i++) {	
		getline(cin, input);	
		lowercase(input);
		query.push_back(input);
	}
	
	for(int i = 0; i < M; i++) {
		vector<string> elemInQuery;
		elemInQuery = splitString(query[i], " ");
		unordered_map<string, int> strMap;
		for(auto s : elemInQuery) {
			strMap.emplace(s, 1);
		}
		int maxSame = 0;
		int maxPara = 0;
		for(int j = 0; j < N; j++) {
			int cnt = 0;
			vector<string> elemInPara = splitString(para[j], " ");
			for(auto s : elemInPara) {
				if(strMap[s] == 1) {
					strMap[s]++;
					cnt++;
				}
			}
			if(cnt > maxSame) {
				maxSame = cnt;
				maxPara = j;
			}
		}
		cout << para[maxPara] <<endl;
		strMap.clear();
	}
	
	return 0;
}
