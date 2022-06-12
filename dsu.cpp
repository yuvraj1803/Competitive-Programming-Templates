template <class T>
class DSU{

private:

    map<T,T> parent;
    set<T> init;
    map<T,int> size;
    void buildParent(){
		
	for(auto node: init){
		parent[node] = node;
		size[node] = 1;
	}
	
    }

public:
    void initSet(set<T> s){
	init = s;
	buildParent();
    }

    int setSize(int x){
	return size[find(x)];
    }
    T find(T x){

        if(parent[x]!=x) return find(parent[x]);
        else return x;
    }

    void set_union(T x, T y){
      size[find(x)] += size[find(y)];
      parent[find(y)] = find(x);
    }
};
