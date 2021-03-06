using Flow = int; using Cost = int;
struct MinCostFlow {
	struct Edge {
		int t; Flow f; Cost c; Edge*next, *rev;
		Edge(int _t, Flow _f, Cost _c, Edge*_next) :
      t(_t), f(_f), c(_c), next(_next) {}
	};

	vector<Edge*> E;

	int addV() { E.pb((Edge*) 0); return len(E) - 1;}

	Edge* makeEdge(int s, int t, Flow f, Cost c) {
		return E[s] = new Edge(t, f, c, E[s]);
	}

	void addEdge(int s, int t, Flow f, Cost c) {
		Edge*e1 = makeEdge(s, t, f, c);
    Edge*e2 = makeEdge(t, s, 0, -c);
		e1->rev = e2, e2->rev = e1;
	}

	pair<Flow, Cost> minCostFlow(int vs, int vt,
                    bool maxFlow) { //flow,cost
		int n = E.size(); Flow flow = 0; Cost cost = 0;
    Cost MAX_COST = inf; Flow MAX_FLOW = inf;
		for (;;) {
			vector<Cost> dist(n, MAX_COST);
			vector<Flow> am(n, 0); vector<Edge*> prev(n);
			vector<bool> inQ(n, false); queue<int> que;

			dist[vs] = 0; am[vs] = MAX_FLOW;
			que.push(vs); inQ[vs] = true;

			while (!que.empty()) {
				int u = que.front(); que.pop();
				Cost c = dist[u]; inQ[u] = false;
				for (Edge*e = E[u]; e; e = e->next)
					if (e->f > 0) {
						Cost nc = c + e->c;
						if (nc < dist[e->t]) {
							dist[e->t] = nc; prev[e->t] = e;
							am[e->t] = min(am[u], e->f);
							if (!inQ[e->t]) {
								que.push(e->t); inQ[e->t] = true;
          } } }
			}

			if (maxFlow) {
				if (dist[vt] == MAX_COST) {
					// //FOR RETRACING FLOW
					// for(int i = 1; i <= nx; i++) {
					// 	for(Edge*e = E[i]; e; e = e->next)
					// 		e->rev->f gives flow bet i and e->t
					// }
					break;
				}
			} else {
				if (dist[vt] >= 0) break;
			}

			Flow by = am[vt]; int u = vt;
			flow += by; cost += by * dist[vt];
			while (u != vs) {
				Edge*e = prev[u];
				e->f -= by; e->rev->f += by; u = e->rev->t;
			}
		}
		return make_pair(flow, cost);
	}
};