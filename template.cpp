#include <bits/stdc++.h>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, 
rb_tree_tag, tree_order_statistics_node_update>;
// order_of_key (k): No. of items < k (strict)
// find_by_order(k): K-th element(counting from 0)

#define pb emplace_back
#define mp make_pair
#define ff first
#define ss second
#define all(v) v.begin(), v.end()
#define len(a) int(a.size())
#define sqrt sqrtl
#define gcd __gcd
#define reset(a, val) memset(a, val, sizeof(a))
#define dbg trace
#define fnu for(int i = 0; i < n; i++)
#define fup(i, s, n) for(int i = s; i < n; i++)
#define initialise reset
#define rev(s) reverse(all(s))
// onlyunique(v) v.erase(unique(all(v)),v.end())
#define vll vector<int>
#define pll pair<int, int>
#define pii pll
#define fast_exp power
#define dbl ld
#define int ll
// copy(a, a+n, ostream_iterator<int>(cout, " "))
mt19937_64 rng(chrono::steady_clock::now()
										.time_since_epoch().count());

#ifdef ONLINE_JUDGE
	#define endl '\n'
	#pragma comment(linker, "/stack:200000000")
	#pragma GCC optimize ("O3")
	#pragma GCC optimize ("O2")
	#pragma GCC optimize("Ofast")
	#pragma GCC optimize ("unroll-loops")
	#pragma GCC target("sse,sse2,sse3,ssse3,sse4,
								popcnt,abm,mmx,avx,tune=native")
	#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef ONLINE_JUDGE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
	template <typename Arg1>
	void __f(const char* name, Arg1&& arg1) {
		cerr << name << " : " << arg1 << endl; }
	template <typename Arg1, typename... Args>
	void __f(const char* names, Arg1&& arg1, 
																Args&&... args){
		const char* comma = strchr(names + 1, ',');
		cerr.write(names, comma-names) << " : " << 
																		arg1 << "  ";
		__f(comma + 1, args...);
	}
#else
#define trace(...)
#endif // ifndef ONLINE_JUDGE

template<typename T> // replace set with vector
ostream& operator<< (ostream& os,const set<T>& v)
{ for (T u: v) os << u << " "; return os; } 
template<typename T, typename S> 
ostream& operator<<(ostream& os,const pair<T,S>& v)
{ os << v.ff << " " << v.ss; return os; } 

struct pair_hash {
	inline size_t operator()(const pii & v) const {
		 return v.ff * 31 + v.ss; }
};

const int mod = 1e9 + 7, inf = 2e18, ninf = -2e18;

int takemod(int a, int mod = mod){ 
	return ((a % mod) + mod) % mod; }

int power(int x, int y, int mod = mod) {
	int ans = 1;
	x = takemod(x, mod);
	while(y) {
		if(y % 2) ans = (x * ans) % mod;
		x = (x * x) % mod;
		y /= 1;
	}	return ans;
}

int modinv(int a, int mod = mod){
	return takemod(power(a, mod-2, mod)); }

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	time_t t1 = clock(), t2;
	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
		freopen("error.txt", "w", stderr);
	#endif

	t2 = clock();
	#ifndef ONLINE_JUDGE
		cerr << "\ntime taken: " << t2-t1 << '\n';
	#endif // ONLINE_JUDGE
	return 0;
}
