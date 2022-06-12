template <class T>
class segment_tree{

/*
before using this data-structure, make sure that:

1. identity variable is set -> second argument in the constructor
2. your merge operation is well-defined


*/

private:

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

  

public:
  
  segment_tree(vector<T> a,T id){
    arr = a;
    while(__builtin_popcount(a.size())!=1) a.push_back(id);
    int N = a.size();
    tree.resize(4*N);
    lazy.resize(4*N);
    identity = id;
    arr = a;
    build_tree(0,0,N-1);
  }

  T query(int l, int r){
    return tree_query(0,0,arr.size()-1,l,r);
  }

  void update(int i, int v){
    point_update(0,0,arr.size()-1, i, v);
  }

  void update(int l, int r, int v){
    range_update(0,0,arr.size()-1, l, r, v);
  }


};