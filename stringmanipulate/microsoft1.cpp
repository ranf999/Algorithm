#include <iostream>
#include <string> 
#include <vector>
#include <cmath>
	
using namespace std;

bool isRoot = true;
class TreeNode 
{
public:
	int possible;
	int itemNum;
	TreeNode* left;
	TreeNode* right;
public:
	TreeNode() {
		this->itemNum = 0;
		this->possible = 100;
		this->left = NULL;
		this->right = NULL;
	}
	TreeNode(int possible, int itemNum) {
		this->possible = possible;
		this->itemNum = itemNum;
		this->left = NULL;
		this->right = NULL;
	}
};

void createTree(TreeNode* root, int itemNum, int P, int Q, int N, int initP)
{
	if(root == NULL)
		return;
	if(root->itemNum == N)
		return;
	int prob = 0;
	

	
	if(P <= 100)
		prob = P;
	else
		prob = 100;
	
	TreeNode* left = new TreeNode(prob, itemNum+1);
	
	
	
	TreeNode* right = NULL;
	if(prob != 100)
		right = new TreeNode(100-prob, 0);
	root->left = left;
	root->right = right;
	
	int newProb;
	newProb = initP/(pow(2,itemNum+1));
	createTree(root->left, itemNum+1, newProb, Q, N, initP);
	createTree(root->right, itemNum, P+Q, Q, N, initP);
}

void printTree(TreeNode* root)
{
	if(!root) return;
		cout<<root->possible<<endl;
	printTree(root->left);
	
	printTree(root->right);
		
}

void expect(TreeNode* root, int depth, double product, vector<double>& path)
{
	if(!root) return;
	
	product = product * (double)root->possible/100.0;
	
	if(root->left == NULL && root->right == NULL)
	{
		path.push_back(product*depth);
	}
	
	expect(root->left, depth+1, product, path);
	expect(root->right, depth+1, product, path);
	
}

int main(void) {
    int P,Q,N;
    cin>>P>>Q>>N;
    
    TreeNode* root = new TreeNode();
    createTree(root, 0, P, Q, N, P);
    printTree(root);
    vector<double> path;
    expect(root, 0, 1, path);
    double sum;
	for(auto num:path){
		sum = sum + num;
	}
	printf("%.2lf\n", sum);
    return 0;
}
