class DSU{
public:
	set<int> s;
	vector<int> parent;
	vector<int> rank;
	DSU(int n){
		parent.resize(n);
		rank.resize(n);
		for(int i=0;i<n;i++){
			s.ins(i);
			parent[i] = i;
			rank[i] = 0;
		}
	}

	int Find(int x){
		if(parent[x]!=x){
			parent[x] = Find(parent[x]);
		}
		return parent[x];
	}

	void Union(int x, int y){
		int xR = Find(x);
		int yR = Find(y);

		if(xR == yR){
			return;
		}

		if(rank[xR] < rank[yR]){
			parent[xR] = yR;
		}else if(rank[xR] > rank[yR]){
			parent[yR] = xR;
		}else{
			parent[xR] = yR;
			rank[yR]++;
		}
	}

	int Same(int x, int y){
		return Find(x) == Find(y);
	}
};
