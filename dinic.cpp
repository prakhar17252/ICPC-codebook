// init(N) where N is no of vertices
// add(u, v, cap) add edge from u to v
// GetMaxFlow(S, T) to get max flow from S to T
// Running time: O(n^3). Very fast in practice
// Solved for N = 5000 in 0.10 seconds on SPOJ
// To get flows, look at edges with non zero flow

const int MAXN = 5000, inf = 2e18;
int src, snk, N, nxt[MAXN+5], dist[MAXN+5];
vector<edge>E[MAXN+5];

struct edge{
	int v, cap, opposite, flow;
};

void init(int _n) { N = _n; }

void add(int u, int v, int cap) {
	E[u].pb({v, cap, len(E[v]), 0});
	E[v].pb({u, 0, len(E[u])-1, 0});
}

bool bfs() {
	reset(dist, -1); dist[src] = 0;
	queue<int> q({src});
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int i = 0; i<E[u].size(); i++) {
			if(E[u][i].cap > E[u][i].flow) {
				int v = E[u][i].v;
				if(dist[v] == -1) {
					dist[v] = dist[u] +1;
					q.push(v);
		} }	}
	} return dist[snk] != -1;
}

int dfs(int u, int sentFlow) {
	if(u == snk || sentFlow == 0) return sentFlow;
	for(; nxt[u] < E[u].size(); nxt[u]++) {
		int v = E[u][nxt[u]].v, c = E[u][nxt[u]].cap;
		int f = E[u][nxt[u]].flow;
		int opposite = E[u][nxt[u]].opposite;
		if(dist[v] == dist[u]+1 && c > f) {
			int tmp = dfs(v,min(sentFlow,c-f));
			if(tmp != 0) {
				E[u][nxt[u]].flow += tmp;
				E[v][opposite].flow -= tmp;
				return tmp;
		}	}
	} return 0;
}

ll GetMaxFlow(int S, int T) {
	src = S; snk = T; ll totalFlow = 0;
	while(bfs()) {
		memset(nxt,0,sizeof(nxt));
		while(int sentFlow = dfs(src,inf))
			totalFlow += sentFlow;
	} return totalFlow;
}
