class DSU{
public:
	set<int> s;
	vector<int> parent;
	vector<int> rank;
	set<int> comps;
	int largestComp;
	map<int,int> sz;
	DSU(int n){
		parent.resize(n);
		rank.resize(n);
		for(int i=0;i<n;i++){
			s.insert(i);
			parent[i] = i;
			comps.insert(i);
			sz[i] = 1;
			rank[i] = 0;
		}
		largestComp = 1;
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
			if(comps.count(xR)) comps.erase(xR);
			sz[yR]+=sz[xR];
			sz[xR] = 0;
			if(sz[yR] > largestComp) largestComp = sz[yR];
		}else if(rank[xR] > rank[yR]){
			parent[yR] = xR;
			if(comps.count(yR)) comps.erase(yR);
			sz[xR]+=sz[yR];
			sz[yR] = 0;
			if(sz[xR] > largestComp) largestComp = sz[xR];
		}else{
			parent[xR] = yR;
			if(comps.count(xR)) comps.erase(xR);
			rank[yR]++;
			sz[yR]+=sz[xR];
			sz[xR] = 0;
			if(sz[yR] > largestComp) largestComp = sz[yR];

		}
	}

	int Same(int x, int y){
		return Find(x) == Find(y);
	} 

	int noComps(){ //returns the number of components
		return (int)comps.size();
	}
	int larComp(){ //returns the largest component
		return largestComp;	
	}
};

