#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <cstdio>
using namespace std;

double calcSum(double first, int n) {
	double sum = first;
    for(int i = 1; i < n; i++) {
    	first = sqrt(first);
        sum = sum + first;
    }
    return sum;
}

int main(void)
{
    double first;
    while(cin>>first) {
    	int num;
        cin >> num;
        double res = calcSum(first,num);
        printf("%.2f\n", res);
    }
    return 0;
}
