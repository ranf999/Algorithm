#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main(){
	//freopen("1.in","r",stdin);
	vector<double> args(4);
	unordered_map<double, double> numMap;
	int n = 0;
	cin >> n;
	int length[n];
	int size = 0;
	for(auto& len : length) {
		cin >> size;
		len = size;
	}
	
	sort(length, length+n);
	int sum = 0;
	for(auto len:length) {
		sum += len;
	}
	int avg = sum/2;
	
//	int w[] = 
	
//	vector<int> weight(w,w+n);
//	vector<int> value(v,v+n);
	vector<vector<int> > dp(n+1, vector<int>(avg+1));
	
	
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= avg; j++){
			if(j < length[i-1])
				dp[i][j] = dp[i-1][j];
			else
				dp[i][j] = max(dp[i-1][j], dp[i-1][j-length[i-1]]+length[i-1]);
		}
	}
	vector<int> res(n+1);
	int total = 0;
	int j = avg;
	for(int i = n; i>0; i--) {
		if(dp[i][j]>dp[i-1][j]) {
			res[i] = 1;
			j = j-length[i-1];
		}
		else
			res[i] = 0;
	}
	
	
	cout << sum - dp[n][avg] << endl;
	return 0;
}
