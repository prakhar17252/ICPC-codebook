/*	graph stores the edges. Kruskal(n) for MST
		spanning_tree will store edges
		mincost will store MST weight */

struct edge {
	int u, v, w;
	edge(int u, int v, int w): u(u), v(v), w(w) {}
	edge(int u, int v): u(u), v(v), w(0) {}
};
/* struct cmp {
		bool operator()(const edge& a, const edge& b)
		const { return a.w < b.w; } }
	set<edge, cmp> s;
	priority_queue<edge, vector<edge>, cmp> q; */
const int N = 1e5 + 10;
vector<edge> graph, spanning_tree;
int mincost = 0, dsu[N], sz[N];

bool edge_sort(const edge &a, const edge &b){
	return a.w < b.w; }

int find(int u){
	return dsu[u] == u ? u : dsu[u] = find(dsu[u]);}

void merge(int u, int v) {
	if(sz[v] > sz[u]) swap(u, v);
	dsu[v] = u;	sz[u] += sz[v]; }

void Kruskal(int n) { //1-based
	sort(all(graph), edge_sort);
	for(int i = 0; i <= n; i++) {
		dsu[i] = i;	sz[i] = 1; 
	}
	for(edge e : graph) {
		int x = find(e.u); int y = find(e.v);
		if(x == y) continue;
		spanning_tree.pb(e); mincost += e.w; merge(x, y);
} }
