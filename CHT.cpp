struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o)const{return k<o.k;}
	bool operator<(ll x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>> {
	const ll inf = 2e18;
	ll div(ll a, ll b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = (x->m > y->m) * inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
  void add(ll k, ll m) { // Add line kx + m
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if(x != begin() && isect(--x, y))
      isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
  // Query maximum kx + m over all inserted lines
	ll query(ll x) {
		assert(!empty()); auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
}; // Fully Dynamic CHT