// initialise with no. of vertices
// To get flows, look at edges with non zero flow
// maxFlow(S, T) to get maxflow from S to T
// Runtime:
// Non-scaling = O(V^2E), lower constant
// Scaling=O(VElog(U)), U is maxEdge capacity
// Scaling = true has higher constant

using T = ll; const bool SCALING = true;
struct Dinic {
  struct Edge {
    int to, from; T cap, flow;
  };

  vector<int> lvl, ptr; vector<vector<Edge>> adj;
  int lim = 1;
  const T INF = numeric_limits<T>::max();

  Dinic(int n) : adj(n+10),lvl(n+10),ptr(n+10){}

  // dir = true for directed edge from a -> b
  void addEdge(int a, int b, T cap, bool dir){
    adj[a].pb({b, len(adj[b]), cap, 0}); 
    adj[b].pb({a, len(adj[a])-1, dir ? 0: cap, 0});
  }

  bool bfs(int s, int t) {
    queue<int> q({s}); reset(lvl, -1); lvl[s] = 0;
    while (!q.empty() && lvl[t] == -1) {
      int v = q.front(); q.pop();
      for (Edge e : adj[v]) {
        if (lvl[e.to] == -1 && e.flow < e.cap && 
            (!SCALING || e.cap - e.flow >= lim)) {
                  q.push(e.to); lvl[e.to]=lvl[v]+1;
        } 
    } } return lvl[t] != -1;
  }

  T dfs(int v, T flow, int t) {
    if (v == t || !flow) return flow;
    for (; ptr[v] < len(adj[v]); ptr[v]++) {
      Edge &e = adj[v][ptr[v]];
      if (lvl[e.to] != lvl[v] + 1) continue;
      T toFlow = min(flow, e.cap - e.flow);
      if (T pushed = dfs(e.to, toFlow, t)) {
        adj[e.to][e.from].flow -= pushed;
        e.flow += pushed; return pushed;
    } } return 0;
  }

  ll maxFlow(int s, int t) {
    ll flow = 0; lim = SCALING ? (1LL << 30) : 1;
    for (; lim > 0; lim >>= 1) {
      while (bfs(s, t)) { reset(ptr, 0);
        while (T pushed = dfs(s, INF, t))
          flow += pushed;
    } } return flow;
  }
};
