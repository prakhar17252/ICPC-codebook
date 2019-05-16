#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std; using namespace __gnu_pbds;

using ll = long long; using pll = pair<int, int>;
using ld = long double; using pii = pair<int, int>;
using dbl = long double; using vll = vector<int>;
template <class T, class cmp = less<T>>
using ordered_set = tree<T, null_type, cmp,
  rb_tree_tag, tree_order_statistics_node_update>;
// order_of_key (k): No. of items < k (strict)
// find_by_order(k): K-th element(counting from 0)

// #defines below :
//int -> ll, pb -> emplace_back, mp -> make_pair
//ff -> first, ss -> second, len(a) -> ll(a.size())
//all(v) -> v.begin(), v.end(), initialise -> reset
//reset(a, val) -> memset(a, val, sizeof(a))
//fnu -> for(int i = 0; i < n; i++), dbg -> trace
//rev(s) -> reverse(all(s)), fast_exp -> power
//onlyunique(v) -> v.erase(unique(all(v)),v.end())
mt19937_64 rng(chrono::steady_clock::now()
										.time_since_epoch().count());

#ifndef ONLINE_JUDGE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
	template <class Arg1>
	void __f(const char* name, Arg1&& arg1) {
		cerr << name << " : " << arg1 << endl; }
	template <class Arg1, class... Args>
	void __f(const char* names, Arg1&& arg1,
																Args&&... args) {
		const char* sep = strchr(names + 1, ',');
		cerr.write(names, sep-names) << " : " <<
																		arg1 << "  ";
		__f(sep + 1, args...);
	}
#else
#define trace(...) 0
#define endl '\n'
// #pragma comment(linker, "/stack:200000000")
#pragma GCC optimize ("O3") // Ofast or O2
#pragma GCC optimize ("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,
//              popcnt,abm,mmx,avx,tune=native")
#define _CRT_SECURE_NO_WARNINGS
#endif // ifndef ONLINE_JUDGE

template<class T> // replace set with vector
ostream& operator << (ostream& os, const set<T>& v)
{ for (T u: v) os << u << ' '; return os; }
template<class T, class S>
ostream& operator<<(ostream& os,const pair<T,S>& v)
{ return os << v.ff << ' ' << v.ss; }

struct pair_hash {
  inline size_t operator()(const pii &v) const
	{ return v.ff * 31 + v.ss; }
};

const ll mod = 1e9 + 7, inf = 2e18, ninf = -2e18;

ll takemod(ll a, ll mod = mod)
{	return ((a % mod) + mod) % mod; }

ll power(ll x, ll y, ll mod = mod) {
	ll ans = 1; x = takemod(x, mod);
	while(y > 0) {
		if(y % 2) ans = (x * ans) % mod;
		x = (x * x) % mod; y /= 2;
	}	return ans;
}

ll modinv(ll a, int mod = mod)
{	return takemod(power(a, mod-2, mod)); }

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	time_t t1 = clock(), t2;
	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
		freopen("error.txt", "w", stderr);
	#endif

	t2 = clock();
	#ifndef ONLINE_JUDGE
		cerr << "\ntime taken: " << t2 - t1 << '\n';
	#endif // ONLINE_JUDGE
	return 0; }
