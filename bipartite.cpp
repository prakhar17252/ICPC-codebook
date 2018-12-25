// Solve() returns maximum bipartite matching
// The match can be recovered using the vector L
// Works with 0 based too. Fast in practice

struct BipartiteMatcher {
  vector<vll> G; vll L, R, Viz;
  
  BipartiteMatcher(int n, int m) :
  G(n), L(n, -1), R(m, -1), Viz(n) {}
  
  void AddEdge(int a, int b) { G[a].pb(b); }
  
  bool Match(int node) {
    if(Viz[node]) return false;
    Viz[node] = true;
    
    for(auto vec: G[node]) {
      if(R[vec] == -1) {
        L[node] = vec; R[vec] = node; return true;
    } }
    
    for(auto vec: G[node]) {
      if(Match(R[vec])) {
        L[node] = vec; R[vec] = node; return true;
		} } return false; }
  
  int Solve() {
    int ok = true;
    while (ok--) {
      fill(all(Viz), 0);
      for(int i = 0; i < len(L); ++i)
        if(L[i] == -1) ok |= Match(i);
    }
    int ret = 0;
    for(int i = 0; i < len(L); ++i) 
			ret += (L[i] != -1);
    return ret; }
};
