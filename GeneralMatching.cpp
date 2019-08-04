// 1-based Vertex index
// Match() -> returns number of edges in matching
// Actual match can be recovered using match array
const int MAXN = 2020 + 1;
int vis[MAXN], par[MAXN], orig[MAXN], match[MAXN];
int aux[MAXN], t, N; vll g[MAXN]; queue<int> Q;

void addEdge(int u, int v){g[u].pb(v); g[v].pb(u);}

void init(int n) {
	N = n; t = 0;
	for (int i = 0; i <= n; ++i) {
		g[i].clear(); match[i] = aux[i] = par[i] = 0;
} }

void augment(int u, int v) {
	int pv = v, nv;
	do {
		pv = par[v]; nv = match[pv];
		match[v] = pv; match[pv] = v; v = nv;
	} while (u != pv);
}

int lca(int v, int w) { ++t;
	while (true) {
		if (v) {
			if (aux[v] == t) return v;
      aux[v] = t; v = orig[par[match[v]]];
		} swap(v, w);
} }

void blossom(int v, int w, int a) {
	while (orig[v] != a) {
		par[v] = w; w = match[v];
		if (vis[w] == 1) { Q.push(w); vis[w] = 0; }
    orig[v] = orig[w] = a; v = par[w];
} }

bool bfs(int u) {
	fill(vis+1,vis+1+N,-1); iota(orig+1,orig+N+1,1);
	Q = queue<int>(); Q.push(u); vis[u] = 0;
	while (!Q.empty()) {
		int v = Q.front(); Q.pop();
		for (int x : g[v]) {
      if (vis[x] == -1) {
        par[x] = v; vis[x] = 1;
        if (!match[x]) return augment(u, x), true;
        Q.push(match[x]); vis[match[x]] = 0;
      } else if (!vis[x] && orig[v] != orig[x]) {
        int a = lca(orig[v], orig[x]);
        blossom(x, v, a); blossom(v, x, a);
  } } }
	return false;
}

int Match() {
	int ans = 0; vector<int> V(N-1);
  iota(all(V), 1); shuffle(all(V), rng);
	for (int x : V) if (!match[x]) {
    for (int y : g[x]) if (!match[y]) {
      match[x] = y, match[y] = x;
      ++ans; break;
  } }
	for (int i = 1; i <= N; ++i)
    if (!match[i] && bfs(i)) ++ans;
	return ans;
}
