// Initialise with no. of vertices
// To get flows, look at edges with positive f in g
// Edge e in g[i] goes from i to e.to
// Runtime:
// Push relabel in O(V^2 E^0.5) with gap heuristic
using T = long long; T INF = 1e18;
struct Edge { int to, rev; T f, c; };

struct MaxFlow {
  vector<vector<Edge>> g; vector<T> ec;
  vector<Edge*> cur; vector<vector<int>> hs;
  vector<int> H;

  MaxFlow(int n) : g(n),ec(n),cur(n),hs(2*n),H(n){}

  void add_edge(int s, int t, T cap, T rcap = 0) {
    if (s == t) return;
    g[s].push_back({t, len(g[t]), 0, cap});
    g[t].push_back({s, len(g[s])-1, 0, rcap});
  }

  void add_flow(Edge& e, T f) {
    Edge &back = g[e.to][e.rev];
    if (!ec[e.to] && f) hs[H[e.to]].pb(e.to);
    e.c -= f; ec[back.to] -= f; back.f -= f;
    e.f += f; ec[e.to] += f; back.c += f; 
  }

  T max_flow(int s, int t) {
    int v = len(g); H[s] = v; ec[t] = 1;
    vector<int> co(2*v); co[0] = v-1;
    for(int i = 0; i < v; ++i)cur[i] = g[i].data();
    for(Edge &e : g[s]) add_flow(e, e.c);
    if(hs[0].size()) {
      for (int hi = 0; hi >= 0;) {
        int u = hs[hi].back(); hs[hi].pop_back();
        while (ec[u] > 0) {
          if (cur[u] == g[u].data() + len(g[u])) {
            H[u] = INF;
            for(Edge &e : g[u]) {
              if (e.c && H[u] > H[e.to]+1)
              { H[u] = H[e.to] + 1, cur[u] = &e; }
            }
            if (++co[H[u]], !--co[hi] && hi < v) {
              for(int i = 0; i < v; ++i)
                if (hi < H[i] && H[i] < v)
                { --co[H[i]]; H[i] = v + 1; }
            }
            hi = H[u];
          }
          else if(cur[u]->c&&H[u]==H[cur[u]->to]+1)
            add_flow(*cur[u],min(ec[u],cur[u]->c));         
          else ++cur[u];
        }
        while (hi >= 0 && hs[hi].empty()) --hi;
    } } return -ec[s]; 
  }
};
