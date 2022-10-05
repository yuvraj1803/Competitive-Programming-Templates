template <class T>
class DSU{
public:
	set<T> s;
	map<T, T> parent;
	map<T,int> rank;
	set<T> comps;
	int largestComp;
	map<T,int> sz;
	DSU (set<T> inp){
		for(auto i:inp){
			s.insert(i);
			parent[i] = i;
			comps.insert(i);
			sz[i] = 1;
			rank[i] = 0;
		}
		largestComp = 1;
	}
	

	T Find(T x){
		if(parent[x]!=x){
			parent[x] = Find(parent[x]);
		}
		return parent[x];
	}

	void Union(T x, T y){
		T xR = Find(x);
		T yR = Find(y);

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

	int Same( T x, T y){
		return Find(x) == Find(y);
	} 

	int noComps(){ //returns the number of components
		return (int)comps.size();
	}
	int larComp(){ //returns the largest component
		return largestComp;	
	}
};
