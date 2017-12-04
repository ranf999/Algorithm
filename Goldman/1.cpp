#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<string> uniqueSubstr(string &s, int k) {
	vector<string> result;
	if (k < 1) return result;
	if (s.size() == 0) return result;
	unordered_set<string> uniqueStringSet;
	for(int i = 0; i + k - 1 < s.size(); i++ ) {
		uniqueStringSet.insert(s.substr(i, k));
	}
	for (auto it = uniqueStringSet.begin(); it != uniqueStringSet.end(); it++) {
		result.push_back(*it);
	}
	return result;	
} 


int main(void) {
	string s;
	int k;
	while (cin >> s >> k) {
		vector<string> result = uniqueSubstr(s, k);
		sort(result.begin(), result.end());
		for (auto s : result) {
			cout << s << endl;
		}
	}
}
