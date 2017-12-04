#include "global.h"


void mSort(vector<int>& A, vector<int> Tmp, int left, int rightEnd) ;

void merge(vector<int>& A, vector<int> Tmp, int left, int right, int rightEnd);

void mergeSort(vector<int>& A)
{
	if(A.size()==0) return;
	int n = A.size();
	vector<int> Tmp(n);
	mSort(A,Tmp,0,n-1);
}

void mSort(vector<int>& A, vector<int> Tmp, int left, int rightEnd)  
{
	if(left < rightEnd)
	{
		int center = (left + rightEnd)/2;
		mSort(A,Tmp,left, center);
		mSort(A,Tmp,center+1,rightEnd);
		merge(A,Tmp,left,center+1,rightEnd);
	}
}

void merge(vector<int>& A, vector<int> Tmp, int left, int right, int rightEnd)
{
	//for(auto n : A)
	//	cout<<n<<" ";
	//	cout << left << " "<<right<<" "<<rightEnd<<endl;
	
	//merge A[left-leftEnd] and A[right-rightEnd] to Tmp;
	int leftEnd = right - 1;
	int Lpos = left;
	int Rpos = right;
	int Tpos = Lpos;
	int num = rightEnd - left + 1;
	while(Lpos <= leftEnd && Rpos <= rightEnd)
		if(A[Lpos] < A[Rpos])
			Tmp[Tpos++] = A[Lpos++];
		else
			Tmp[Tpos++] = A[Rpos++];
	while(Lpos <= leftEnd)
		Tmp[Tpos++] = A[Lpos++];
	while(Rpos <= rightEnd)
		Tmp[Tpos++] = A[Rpos++];

	for(int i = 0; i < num; i++)
	{
		A[rightEnd] = Tmp[rightEnd];
		rightEnd--;
	}
	
}

