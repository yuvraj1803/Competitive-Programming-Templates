#include <bits/stdc++.h>

using namespace std;

#define bug(x) cout << #x << ':' << x << '\n';

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
	for(vector<T> i:v){
		cout << i << '\n';
	}
	return out;
}

template <typename T>
void print([[maybe_unused]]T x){
	bug(x)
}
