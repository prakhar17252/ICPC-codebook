struct SCC {
	int V, group_cnt;
	vector<vector<int>> adj, radj;
	vector<int> group_num, vis;
	stack<int> stk;

	// V = number of vertices. 0 based indexing
	SCC(int V): V(V), group_cnt(0), group_num(V),
										vis(V), adj(V), radj(V) {}

	// Call this to add an edge
	void add_edge(int v1, int v2) {
		adj[v1].pb(v2); radj[v2].pb(v1);
	}

	void fill_forward(int x) {
		vis[x] = true;
		for (int v: adj[x]) {
			if(!vis[v]) fill_forward(v);
		} stk.push(x);
	}

	void fill_backward(int x) {
		vis[x] = false;
		group_num[x] = group_cnt;
		for (int v: radj[x]) {
			if(vis[v]) fill_backward(v);
	} }

	// Returns no. of SCCs
	// group_num contains component assignments
	int get_scc() {
		for (int i = 0; i < V; i++) {	// 0 based
			if (!vis[i]) fill_forward(i);
		}
		group_cnt = 0;
		while (!stk.empty()) {
			if (vis[stk.top()]) {
				++group_cnt;
				fill_backward(stk.top());
			} stk.pop();
		} return group_cnt;
	}
};
