## No.1
```java  

	#include "ancester.h"
	
	string solution::getNearestCommonAncester(string input)
	{
		vector<string> relations;
		relations = splitString(input, ",");
		int len = relations.size();
		TreeNode* root = NULL;
		unordered_map<string, TreeNode* > treeMap;
		root = generateTree(relations, treeMap);
		TreeNode *res = getLCA(root, findTreeNode(relations[len-2], treeMap), findTreeNode(relations[len-1], treeMap), root);
		if(res == NULL) return "No";
		return res->name;
	}
	
	
	
	TreeNode* solution::generateTree(vector<string> &input, unordered_map<string, TreeNode* > &treeMap)
	{ 
		int len = input.size();
		TreeNode* root = NULL;
		if(len < 3) return root;
		for(int i = 0; i < len-2; i++) {
			vector<string> relation;
			relation = splitString(input[i], "->");
			TreeNode *parent;
			TreeNode *child;
			unordered_map<string, TreeNode*>::const_iterator got = treeMap.find(relation[0]);
			if(got == treeMap.end()) {
				parent = new TreeNode(relation[0]);
				treeMap.emplace(relation[0], parent);
			}
			else 
				parent = treeMap[relation[0] ];
	
			if(root == NULL)
				root = parent;
	
			got = treeMap.find(relation[1]);
			if(got == treeMap.end()) {
				child = new TreeNode(relation[1]);
				treeMap.emplace(relation[1],child);
			}
			else
				child = treeMap[relation[1] ];
			parent->children.push_back(child);
			child->parent = parent;
			if(root == child)
				root = parent;
		}
		
		//printTree(root);
		return root;
	}
	
	void solution::printTree(TreeNode* root)
	{
		if(!root) return;
		for(auto child : root->children)
			printTree(child);
		cout<<root->name<<endl;	
	}
	
	
	
	vector<string> solution::splitString(const string &s, const string &seperator)
	{
		vector<string> v;
		size_t pos1, pos2;
		pos1 = 0;
		pos2 = s.find(seperator, pos1);
		while(string::npos != pos2) {
			v.push_back(s.substr(pos1, pos2 - pos1));
			pos1 = pos2 + seperator.size();
			pos2 = s.find(seperator, pos1);
		}
		if(pos1 != s.length())
			v.push_back(s.substr(pos1));
		return v;
	}
	
	
	TreeNode* solution::findTreeNode(const string &s, unordered_map<string, TreeNode* > &treeMap)
	{
		TreeNode* node = NULL;
		node = treeMap[s];
		return node;
	}
	
	int solution::getDepth(TreeNode* node)
	{
		int d = -1;
	    while (node)
	    {
	        ++d;
	        node = node->parent;
	    }
	    return d;
	}
	
	TreeNode* solution::getLCA(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode *wholeRoot)
	{
		int depth_1 = getDepth(p);
		int depth_2 = getDepth(q);
		
		if(depth_1 < depth_2) {
			TreeNode* tmp = p;
			p = q;
			q = tmp;
			int tmp_depth = depth_1;
			depth_1 = depth_2;
			depth_2 = tmp_depth;
		}
		int finalDepth = depth_2 - 1;
		if(finalDepth < 0) return NULL;
		
		int diff = depth_1 - depth_2;
		
		while(diff > 0) {
			p = p->parent;
			depth_1--;
			diff--;
		}
		
		while( p && q ) {
			if( p == q ) {
				if(depth_1 <= finalDepth)
				    return p;
				else
				    return p->parent;
			}
			p = p->parent;
			q = q->parent;
			depth_1--;
			depth_2--;
		}
		return NULL;
			
	}
```
