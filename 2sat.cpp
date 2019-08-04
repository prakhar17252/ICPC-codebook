/*  init() initializes 2-SAT arrays.
    solve() checks if a valid solution exists
    mark[u] stores the bool value of the node u 
    Use mark[] to recover the final solution
    Notes on Indexing Nodes :
    n = Number of Nodes(excluding negation)
    u = 2k, !u = 2k + 1
    Nodes are 0-indexed. [0, NUM_VERTICES) */

const int N = (int) 5e5 + 10;
int NUM, id, n, arr[N*2]; 
vector<int> adj[N*2];
bool mark[N*2];

inline bool dfs(int node){
  if (mark[node^1]) return false;
  if(mark[node]) return true;
  mark[node] = true;
  arr[id++] = node;
  for(int i: adj[node]) 
    if(!dfs(i)) return false;
  return true;
}

inline void init(){
  NUM = 2*n; reset(mark, 0);
  for(int i = 0; i < NUM; i++) adj[i].clear();
}

// Adds the clause (u or v) 
inline void addOr(int u, int v){
  adj[u^1].push_back(v); adj[v^1].push_back(u);
}

// Adds the clause (u == v) 
inline void addEquivalent(int u, int v){
  adj[u].push_back(v); adj[v].push_back(u);
  adj[u^1].push_back(v^1); 
  adj[v^1].push_back(u^1);
}

// Adds the clause (u xor v)
inline void addXor(int u, int v){
  addOr(u, v); addOr(u^1, v^1);
}

// Forces variable (u) to be true
inline void forceTrue(int u){
  adj[u^1].push_back(u);
}

// Forces variable (u) to be false
inline void forceFalse(int u){forceTrue(u^1);}

// Adds the clause (u and v) 
inline void addAnd(int u, int v){
  forceTrue(u); forceTrue(v);
}

inline void addImplication(int u, int v){
	adj[u].push_back(v);
}

// Returns true if a solution exists.
inline bool solve(){
  for(int i = 0; i < NUM; i++){
    sort(all(adj[i])); onlyunique(adj[i]);
  }
  for(int i = 0; i < NUM; i += 2){
    if((!mark[i]) && (!mark[i+1])){
      id = 0;
      if(!dfs(i)){
        while(id > 0) mark[arr[--id]] = false;
        if(!dfs(i+1)) return false;
      }
    }
  }
  return true;
}
