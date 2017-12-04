#include<iostream>
#include<vector> 

using namespace std;

class UnionFind {
public:
	vector<int> parent;
	vector<int> size;
	int cnt;
public:
	UnionFind(int n) {
		cnt = n;
		for(int i = 0; i < n; i++) {
			parent.push_back(i);
			size.push_back(1);
		}
	}
	int count();
	int find(int p);
	bool connected(int p, int q);
	void union2(int p, int q);
};

int UnionFind::count() {
	return cnt;
}

int UnionFind::find(int p) {
	int root = p;
	while(root != parent[root]) {
		root = parent[root];
	}
	while(root != p) {
		int newp = parent[p];
		parent[p] = root;
		p = newp;
	}
	return root;
}

bool UnionFind::connected(int p, int q) {
	return find(p) == find(q);
}

void UnionFind::union2(int p, int q) {
	int rootP = find(p);
	int rootQ = find(q);
	if(rootP == rootQ) return;
	if(size[rootP] < size[rootQ]) {
		parent[rootP] = rootQ;
		size[rootQ] += size[rootP];
	} else {
		parent[rootQ] = rootP;
		size[rootP] += size[rootQ];
	}
	cnt--;
}


int main(void) {
	UnionFind uf(10);
	uf.union2(1,2);
	uf.union2(2,3);
	uf.union2(6,7);
	uf.union2(6,8); 
	cout << uf.cnt << endl;	
}

