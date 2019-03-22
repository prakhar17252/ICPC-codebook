// The match can be recovered using the vector L
// Works with 1 based only. Very Fast in practice.
// init with n, m -> sz of grp 1 & 2 (bipartite)
// addEdge(x, y) -> edge b/w x of grp1, y of grp2
struct BipartiteMatcher { // O(E V^0.5)
  vector<vll> graph; vll L, R, dist;
  const int NIL = 0; int n, m;
  BipartiteMatcher(int n, int m) : n(n), m(m), 
          graph(n+1), L(n+1), R(m+1), dist(n+1) {}

  void add_edge(int u, int v) { graph[u].pb(v); }
  bool BFS() {
    queue<int> q; dist[NIL] = inf;
    for (int i = 1; i <= n; i++) {
      if (L[i] == NIL) { dist[i] = 0; q.push(i); }
      else dist[i] = inf;
    }
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (dist[u] >= dist[NIL]) continue;
      for (int v : graph[u]) if (dist[R[v]] == inf)
      { dist[R[v]] = dist[u]+1; q.push(R[v]); }
    } return dist[NIL] != inf; }

  bool DFS(int u) {
    if (u == NIL) return true;
    for (int v : graph[u])
      if (dist[R[v]] == dist[u] + 1 && DFS(R[v]))
      { L[u] = v; R[v] = u; return true; }
    dist[u] = inf; return false; }

  int maximum_matching() { // fill L, R with NIL
    int mat = 0; fill(all(L),NIL),fill(all(R),NIL);
    while (BFS()) for (int i = 1; i <= n; i++)
      if (L[i] == NIL && DFS(i)) mat++;
    return mat; }
};
