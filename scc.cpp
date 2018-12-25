struct SCC {
	int V, group_cnt;
	vector<vector<int>> adj, radj;
	vector<int> group_num, vis, stk;
	stack<int> stk;

	// V = number of vertices
	SCC(int V): V(V), group_cnt(0), group_num(V),
										vis(V), adj(V), radj(V) {}
                    
	void add_edge(int v1, int v2) {
		adj[v1].pb(v2); radj[v2].pb(v1);
	}

	void fill_forward(int x) {
		vis[x] = true;
		for (int v: adj[x]) {
			if(!vis[v]) fill_forward(v);
		} stk.pb(x);
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
		for (int i = 0; i < V; i++) {
			if (!vis[i]) fill_forward(i);
		}
		group_cnt = 0;
		while (!stk.empty()) {
			if (vis[stk.back()]) {
				fill_backward(stk.back());
				group_cnt++;
			} stk.pop_back();
		} return group_cnt;
	}
};
