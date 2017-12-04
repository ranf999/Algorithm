#include "Outthink.h"

void solution1::printLine(int num, int p, int q)
{
	for(int i = 1; i <= num; i++) {
		bool div = divisible(i, p, q);
		bool cont = contain(i, p, q);
		if(div)
			cout<<"OUT";
		if(cont)
			cout<<"THINK";
		if(!div && !cont)
			cout<<i;
		if(i < num)
			cout<<",";
	}
}

bool solution1::divisible(int i, int p, int q)
{
	if(i % p == 0 || i % q == 0)
		return true;
	else
		return false;
}

bool solution1::contain(int i, int p, int q)
{
	while(i % 10 != 0) {
		if(i % 10 == p || i % 10 == q)
			return true;
		else 
			i /= 10;
	}
	return false;
}
