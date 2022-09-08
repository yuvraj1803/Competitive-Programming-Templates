#include <bits/stdc++.h

using namespace std;


class DSU{
public:
	set<pair<int,int>> s;
	map<pair<int,int>, pair<int,int>> parent;
	map<pair<int,int>,int> rank;
	set<pair<int,int>> comps;
	int largestComp;
	map<pair<int,int>,int> sz;
	DSU(int n, int m){
		for(int i=0;i<n;i++){
            
            for(int j=0;j<m;j++){
                s.insert({i,j});
                parent[{i,j}] = {i,j};
                comps.insert({i,j});
                sz[{i,j}] = 1;
                rank[{i,j}] = 0;
            }
            
		}
		largestComp = 1;
	}

	pair<int,int> Find(pair<int,int> x){
		if(parent[x]!=x){
			parent[x] = Find(parent[x]);
		}
		return parent[x];
	}

	void Union(pair<int,int> x, pair<int,int> y){
		pair<int,int> xR = Find(x);
		pair<int,int> yR = Find(y);

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

	int Same(pair<int,int> x, pair<int,int> y){
		return Find(x) == Find(y);
	} 

	int noComps(){ //returns the number of components
		return (int)comps.size();
	}
	int larComp(){ //returns the largest component
		return largestComp;	
	}
};


int main(){
  
  DSU d(n,m); // for nxm grid.
  
  return 0; 
}
