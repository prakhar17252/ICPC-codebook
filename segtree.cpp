const int N = 1e5 + 10;
int seg[4*N], lz[4*N], a[N], n;

#define lc cur + cur
#define rc cur + cur + 1
#define mid (s + e) / 2

int merge(int x, int y) { return x + y; }
int cnt(int l, int r){ return r-l+1; } // 1 for RMQ

void build(int cur, int s, int e) {
	if(s == e) { seg[cur] = a[s]; return; }
  build(lc, s, mid); build(rc, mid+1, e);
  seg[cur] = merge(seg[lc], seg[rc]);
}

void propogate(int cur, int s, int e) {
  if(s != e){lz[lc] += lz[cur]; lz[rc] += lz[cur];}
  seg[cur] += cnt(s, e) * lz[cur]; lz[cur] = 0;
}

void update(int cur, int s, int e,
                          int l, int r, int val) {
  propogate(cur, s, e);
  if(e < l || s > r) return;
  if(l <= s && e <= r)
  { lz[cur] += val; propogate(cur, s, e); return; }
  update(lc, s, mid, l, r, val);
  update(rc, mid+1, e, l, r, val);
  seg[cur] = merge(seg[lc], seg[rc]);
}

int query(int cur, int s, int e, int l, int r) {
  propogate(cur, s, e);
  if(e < l || s > r) return 0; // -inf for RMQ
  if(l <= s && e <= r) return seg[cur];
  int q1 = query(lc, s, mid, l, r);
  int q2 = query(rc, mid+1, e, l, r);
  return merge(q1, q2);
}

void build() { build(1, 1, n); }
void update(int pos, int val)
{ update(1, 1, n, pos, pos, val); }
void update(int l, int r, int val)
{ update(1, 1, n, l, r, val); }
int query(int l, int r)
{ return query(1, 1, n, l, r); }

// Number of elements <= k in [l, r]
// upper_bound(all(seg[cur]), k) - seg[cur].begin();
// Number of elements >= k in [l, r]
// seg[cur].end() - lower_bound(all(seg[cur]), k);
/* Replace lower & upper to remove equality sign */

// merge(all(seg[lc]), all(seg[rc]),
//                       back_inserter(seg[cur]));
