//Author: Yuvraj Sakshith
#include <bits/stdc++.h>
#define pb              push_back
#define int             long long
#define ff              first
#define ss              second
#define all(a)          a.begin(),a.end()
#define ed              '\n'
#define print(x)        cout << #x << " = " << x << "\n";
#define ins             insert

using namespace std;
using vi = vector<int>;
using vvi = vector<vector<int>>;

[[maybe_unused]] const int MOD = 1e9+7;
[[maybe_unused]] const int inf = 1e18;
[[maybe_unused]] const int nax = 1e5;
bool sieve[nax];


int binpow(int a, int b, int m) {
    a %= m;
    int res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

void prime_sieve(){
	memset(sieve, 1, sizeof(sieve));
	sieve[0] = sieve[1] = 0;
	sieve[2] = 1;
	for(int i=2;i*i<=nax;i++){
		if(sieve[i]){
			for(int j=i*i;j<=nax;j+=i){
				sieve[j] = 0;
			}
		}
	}
}

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

template <class T>
class segment_tree{

/*
before using this data-structure, make sure that:

1. identity variable is set -> second argument in the constructor
2. your merge operation is well-defined


*/

	public:

  vector<T> tree;
  vector<T> lazy; // lazy-tree
  vector<T> arr;
  T identity;  //this is what is returned if the current range is disjoint in a few recursive functions defined below.

  T operation(T x, T y){ 
    return x + y;
  }

  T merge(T x, T y){   // this is the merge function which merges two nodes in the tree
    return operation(x,y);
  }

  void build_tree(int i, int l, int r){
      if(l==r) tree[i] = arr[l];
      else{

        int mid = l + (r-l)/2;

        build_tree(2*i+1, l,mid);
        build_tree(2*i+2, mid+1,r);
        tree[i] = merge(tree[2*i+1], tree[2*i+2]);
      }
  }

  T tree_query(int i, int lo, int hi, int l, int r){
    if(lo>=l and hi<=r) return tree[i];

    if(l>hi || r<lo) return identity;

    int m = lo + (hi-lo)/2;
    return operation(tree_query(2*i+1, lo, m, l,r), tree_query(2*i+2,m+1,hi,l,r));
  }

  void point_update(int ix, int lo, int hi, int i, T v){ // increments by value v, it does not replace by a value v.

    if(lo == hi) tree[ix] = operation(tree[ix],v);
    else{
      int m = lo + (hi-lo)/2;
      if(ix<=m and ix>=lo) point_update(2*ix+1,lo,m, i, v);
      else point_update(2*ix+2, m+1, hi, i, v);
      tree[ix] = merge(tree[2*ix+1],tree[2*ix+2]);
    }
  }

  void range_update(int ix, int lo, int hi, int l, int r, int v){
      if(lazy[ix]!=identity){
        int times = (hi - lo + 1);
        T final = identity;
        for(int i=0;i<times;i++) final = operation(final, lazy[ix]);
        tree[ix] = final;
        if(lo!=hi){
          lazy[2*ix + 1] = operation(lazy[2*ix + 1], lazy[ix]);
          lazy[2*ix + 2] = operation(lazy[2*ix + 2], lazy[ix]);

        }
        lazy[ix] = identity;
      } 

      if(r < lo || l > hi || lo > hi) return;

      if(lo >= l and hi <= r){
        int times = (hi - lo + 1);
        T final = identity;
        for(int i=0;i<times;i++) final = operation(final, v);
        tree[ix] = final;
        if(lo!=hi){
          lazy[2*ix + 1] = operation(lazy[2*ix + 1], v);
          lazy[2*ix + 2] = operation(lazy[2*ix + 2], v);
        }
        return;

      }

      int mid = (lo + hi) >> 1;
      range_update(2*ix + 1, lo, mid, l, r, v);
      range_update(2*ix + 2, mid + 1, hi, l, r, v);
      tree[ix] = merge(tree[2*ix + 1], tree[2*ix + 2]);
  }

  T lazy_query(int ix, int lo, int hi, int l, int r){
      if(lazy[ix] != identity){
        int times = (hi - lo + 1);
        T final = identity;
        for(int i=0;i<times;i++) final = operation(final, lazy[ix]);
        tree[ix] = final;
        if(lo!=hi){
          lazy[2*ix + 1] = operation(lazy[2*ix + 1], lazy[ix]);
          lazy[2*ix + 2] = operation(lazy[2*ix + 2], lazy[ix]);

        }
        lazy[ix] = identity;
      }

      if(r < lo || l > hi || lo > hi) return  identity;
      if(lo >= l and hi <= r){
        return tree[ix];
      }

      int mid = (lo + hi) >> 1;
      return operation(lazy_query(2*ix + 1, lo, mid, l,r), lazy_query(2*ix + 2, mid + 1, hi, l, r));
  }

  

public:
  
  segment_tree(vector<T> a,T id){
    arr = a;
    while(__builtin_popcount(a.size())!=1) a.push_back(id);
    int N = a.size();
    tree.resize(4*N);
    lazy.resize(4*N);
	tree.assign(4*N, id);
	lazy.assign(4*N, id);
    identity = id;
    arr = a;
    build_tree(0,0,N-1);
  }

  T query(int l, int r){
    return lazy_query(0,0,arr.size()-1,l,r);
  }

  void update(int i, int v){
    range_update(0,0,arr.size()-1, i, i, v);
  }

  void update(int l, int r, int v){
    range_update(0,0,arr.size()-1, l, r, v);
  }


};


template <typename T1, typename T2>
ostream &operator << (ostream &out, pair<T1,T2> p){
	cout << '{' << p.ff << ',' << p.ss << '}';
	return out;
}
template <typename T>
ostream &operator << (ostream &out, vector<T> v){
    for(T i:v) cout << i << ' ';
    return out;
}
template <typename T>
ostream &operator << (ostream &out, multiset<T> m){
	for(T i:m) cout << i << ' ' ;
	return out;
}
template <typename T>
ostream &operator << (ostream &out, set<T> s){
	for(T i:s) cout << i << ' ';
	return out;
}
template <typename T>
ostream &operator << (ostream &out, vector<vector<T>> v){
	for(vi i:v){
		cout << i << ed;
	}
	return out;
}


void solve(){
	
   
}

signed main(){
      ios_base::sync_with_stdio(0);cin.tie(0);
      int t = 1;
//	  prime_sieve();
      #ifdef mtc
      cin >> t;
      #endif
      for(int i=1;i<=t;i++){
      	#ifdef case
        cout << "Case #" << i << ": ";
	#endif
        solve();
      }

}
















