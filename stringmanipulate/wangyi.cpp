// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

//2
//<diary><color = red>I am happy.<color = blue>I am sad.< / color>I am happy.< / color>This is black.< / diary>
//<diary><color = ab>12< / color><color = a>12< / color><color = aa>12< / color>< / diary>

int main()
{
	int n = 0;
	string input;
	while (cin >> n) {
		for (int i = 1; i <= n; i++) {
			getline(cin, input);
			cout << "Case " << n << endl;
			cout << input << endl;
		}
	}
    return 0;
}


