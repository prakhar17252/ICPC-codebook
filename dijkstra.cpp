const int N = 1e5 + 10;
vector<pii> adj[N];
bool vis[N] = {0}; int d[N];
void dijkstra(int v, int n){
	fill(d, d+n, inf); d[v] = 0;
	priority_queue<pii, vector<pii>,
							greater<pii>> pq;
	pq.push(mp(d[v], v));
	while(!pq.empty()){
		int u = pq.top().ss; pq.pop();
		if(vis[u]) continue; vis[u] = true;
		for(auto &it: adj[u]) {
			if(d[it.ff] > d[u] + it.ss) {
				d[it.ff] = d[u] + it.ss;
				pq.push({d[it.ff], it.ff});
			}
		}
	}
}
