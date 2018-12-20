/* 	Running time: O(|V|^2 |E|)
		INPUT:
				- graph, constructed using AddEdge()
				- source and sink
		OUTPUT:
				- maximum flow value
				- To obtain actual flow values, 
					look at edges with capacity > 0 (zero
					capacity edges are residual edges) */
struct Edge{
	int u, v; ll cap, flo;
	Edge() {}
	Edge(int u, int v, ll cap): 
		u(u), v(v), cap(cap), flo(0) {}
};

struct Dinic{
	int N; vector<Edge> E;
	vector<vector<int>> g;
	vector<int> d, pt;

	Dinic(int N): N(N), E(0), g(N), d(N), pt(N){}

	void AddEdge(int u, int v, ll cap){
		if(u != v){
			E.emplace_back(u, v, cap);
			g[u].emplace_back(E.size() - 1);
			E.emplace_back(v, u, 0);
			g[v].emplace_back(E.size() - 1);
		}	
	}

	bool BFS(int S, int T){
		queue<int> q({S});
		fill(all(d), N+1); d[S] = 0;
		while(!q.empty()){
			int u = q.front(); q.pop();
			if(u == T) break;
			for(int k: g[u]){
			 Edge &e = E[k];
			 	if(e.flo < e.cap && d[e.v] > d[e.u]+1){
					d[e.v] = d[e.u] + 1; q.emplace(e.v);
				}
			}
		}	return d[T] != N+1;
	}

	ll DFS(int u, int T, ll flo = -1){
		if(u == T || flo == 0) return flo;
		for(int &i = pt[u]; i < len(g[u]); ++i){
			Edge &e = E[g[u][i]];
			Edge &oe = E[g[u][i]^1];
			if(d[e.v] == d[e.u] + 1){
				ll amt = e.cap - e.flo;
				if(flo != -1 && amt > flo) amt = flo;
				if(ll pushed = DFS(e.v, T, amt)){
					e.flo += pushed; oe.flo -= pushed;
					return pushed;
				}
			}
		} return 0;
	}

	ll MaxFlow(int S, int T){
		ll total = 0;
		while(BFS(S, T)){
			fill(all(pt), 0);
			while(ll flo = DFS(S, T)) total += flo;
		} return total;
	}
};
