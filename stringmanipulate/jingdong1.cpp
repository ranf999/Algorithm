#include <iostream>
#include <vector>
using namespace std;
int maxVal(vector<vector<int> > matrix) {
    if(matrix.size() == 0) return 0;
    int m = matrix.size();
    int n = matrix[0].size();
    int opt[m][n];
    opt[0][0] = matrix[0][0];
    for(int i = 1; i < n; i++) {
        opt[0][i] = opt[0][i-1] + matrix[0][i];
    }
    for(int j = 1; j < m; j++) {
        opt[j][0] = opt[j-1][0] + matrix[j][0];
    }
    for(int i = 1; i < m; i++) {
        for(int j = 1; j < m; j++) {
            opt[i][j] = max(opt[i-1][j], opt[i][j-1]) + matrix[i][j];
        }
    }
    return opt[m-1][n-1];
}

int main() {
    
    return 0;
}
