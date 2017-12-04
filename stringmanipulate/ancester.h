#ifndef _ANCESTER_H_
#define _ANCESTER_H_

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class TreeNode {
public:
	string name;
	vector<TreeNode*> children;
	TreeNode* parent;
	TreeNode(string name) {
		this->name = name;
		this->parent = NULL;
	}
};


class solution {
public:
	string getNearestCommonAncester(string input);
	TreeNode* generateTree(vector<string> &input, unordered_map<string, TreeNode* > &treeMap);
int getDepth(TreeNode* node);
void deleteTree(TreeNode *root);
vector<string> splitString(const string &s, const string &seperator);
TreeNode* findTreeNode(const string &s, unordered_map<string, TreeNode* > &treeMap);
TreeNode* getLCA(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode *wholeRoot);
void printTree(TreeNode* root);

};



#endif
