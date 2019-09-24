// Initialise with the first few terms and modulo.
// There should be atleast 2*M terms,
// where M is degree of recurrence.
// To obtain k'th term, call nth_term(k);

struct LinearRecurrence {
  vi terms; int m; ll mod;
  vll a, h, t_, s, t;
  LinearRecurrence(vi terms, ll mod = ::mod) :
                      terms(terms), mod(mod) {}

  vi BM(vi x) {
    vi ls, cur; int lf, l;
    for (int i = 0; i < len(x); ++i) {
      ll t = 0;
      for (int j = 0; j < len(cur); ++j)
        t = (t + x[i-j-1] * (ll) cur[j]) % mod;
      if ((t - x[i]) % mod == 0) continue;
      if (cur.empty()) {
        cur.resize(i+1);
        lf = i; l = (t - x[i]) % mod; continue;
      }
      ll k = -(x[i]-t) * power(l,mod-2,mod) % mod;
      vi c(i - lf - 1); c.pb(k);
      for (int j = 0; j < ls.size(); ++j)
        c.pb(-ls[j] * k % mod);

      if (len(c) < len(cur)) c.resize(len(cur));
      for (int j = 0; j < len(cur); ++j)
        c[j] = (c[j] + cur[j]) % mod;

      if (i - lf + len(ls) >= len(cur))
      { ls = cur; lf = i; l = (t - x[i]) % mod; }
      cur = c;
    }
    for (int i = 0;i < cur.size(); ++i)
      cur[i] = (cur[i] % mod + mod) % mod;
    return cur;
  }

  void mull(vll &p, vll &q) {
    for (int i = 0; i < m + m; ++i) t_[i] = 0;
    for (int i = 0; i < m; ++i) if (p[i])
      for (int j = 0; j < m; ++j)
        t_[i+j] = (t_[i+j] + p[i] * q[j]) % mod;

    for (int i = m + m - 1; i >= m; --i) if (t_[i])
      for (int j = m - 1; ~j; --j)
        t_[i-j-1] = (t_[i-j-1] + t_[i]*h[j]) % mod;

    for (int i = 0; i < m; ++i) p[i] = t_[i];
  }

  ll calc(ll K) {
    for (int i = m; ~i; --i) s[i] = t[i] = 0;
    s[0] = 1;
    if (m != 1) t[1] = 1;
    else t[0] = h[0];

    while (K > 0) {
      if (K % 2) mull(s, t);
      mull(t, t); K /= 2;
    }

    ll su = 0;
    for (int i = 0; i < m; ++i)
      su = (su + s[i] * a[i]) % mod;
    return (su % mod + mod) % mod;
  }

  int nth_term(ll n) {
    if (n < terms.size()) return terms[n];
    vi v = BM(terms); m = v.size();
    a = h = t_ = s = t = vll(2 * m, 0);
    if (m == 0) return 0;
    for (int i = 0; i < m; ++i)
    { h[i] = v[i]; a[i] = terms[i]; }
    return calc(n);
  }
};