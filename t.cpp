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

















