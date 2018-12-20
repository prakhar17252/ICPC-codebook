const int N = 1e5 + 10;
vector<int> adj[N], cutPts;
vector<pll> bridges; bool visited[N] = {0};

// Use p = -1 for root
void dfs(int u, int p = -1, int d = 0){
	visited[u] = true;
	dep[u] = fup[u] = d;
	bool isCutpt = false;
	for(int &v: adj[u]){
		if(v == p) continue;
		if(!visited[v]){
			dfs(v, u, d+1);
			fup[u] = min(fup[u], fup[v]);
			//Cut-Vertices
			if(fup[v] >= dep[u]){
				//Excluding root
				if(p != -1) isCutpt = true;
				//For root
				else if(adj[u].size() > 1) 
					isCutpt = true;
			}
			//Bridges
			if(fup[v] > dep[u]) bridges.pb(mp(u,v));
			
		}
		else fup[u] = min(fup[u], dep[v]);		 
	}
	//Cut - Vertices
	if(isCutpt) cutPts.pb(u);
}
