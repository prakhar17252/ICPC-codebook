// Ranges in SegmentTree, out[v] = in[v] + sz[v]
// in[head[v]] to in[v] : path from head[v] to v
// in[v] to out[v] - 1 : subtree of v 
// in[v] : node v
struct HeavyLight {
  int n, t = 1;
  vector<vector<int>> g; SegmentTree seg;
  vector<int> in, out, sz, par, head, depth;

  HLD(int n) : n(n), g(n+1), in(n+1), out(n+1), 
    sz(n+1),par(n+1),head(n+1),seg(n),depth(n+1){}

  void addEdge(int u,int v){g[u].pb(v);g[v].pb(u);}
  
  void dfs_sz(int v, int p) {
    sz[v] = 1; par[v] = p; depth[v] = depth[p] + 1;
    for (int &u : g[v]) if (u != p) {
      dfs_sz(u, v); sz[v] += sz[u];
      if (sz[u] > sz[g[v][0]]) swap(u, g[v][0]);
  } }

  void dfs_hld(int v, int p) {
    in[v] = t++;
    for (int &u : g[v]) if (u != p) {
      head[u] = (u == g[v][0] ? head[v] : u);
      dfs_hld(u, v);
    } out[v] = t; }

  void doHLD()
  { dfs_sz(1, 0); dfs_hld(1, 0); seg.build(); }

  int query(int u, int v) { // path between u, v
    int ans = 0;
    while (head[u] != head[v]) {
      if(depth[head[u]]>depth[head[v]]) swap(u, v);
      ans = max(ans,seg.query(in[head[v]], in[v]));
      v = par[head[v]]; 
    }
    if (depth[u] > depth[v]) swap(u, v);
    ans = max(ans, seg.query(in[u], in[v]));
    return ans; }
};
