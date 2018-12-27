vector<queue<int>> M; vector<vector<int>> F; int n;

vector<pii> SMP() {
	vector<int> hus(n+1, -1);	queue<int> q;
	for(int i = 1; i <= n; i++) q.push(i);
	while(!q.empty()) {
		int husb = q.front(); q.pop();
		int wife = M[husb].front(); M[husb].pop();
		if(hus[wife] == -1) {
			hus[wife] = husb;
		} else if(F[wife][hus[wife]] > F[wife][husb]) {
			swap(hus[wife], husb); q.push(husb);
		} else q.push(husb);
	}
	vector<pii> res;
	for(int i = 1; i <= n; i++)	{
		res.pb(mp(hus[i], i));
	} return res;
}

int main() {
	// n is number of marriages
	cin >> n; M.resize(n+1); F.resize(n+1);
	for(int i = 0; i < n; i++) {
		// First line is the woman in question
		int r; cin >> r;
		vector<int> cur(n+1);
		// Next n elements is husbands listed in rank
		// Earlier is better
		for(int j = 0; j < n; j++) {
			int x; cin >> x;
			cur[x] = j;
		} F[r] = cur;
	}
	// Same for men as women
	for(int i = 0; i < n; i++) {
		int r; cin >> r;
		queue<int> cur;
		for(int j = 0; j < n; j++) {
			int x; cin >> x;
			cur.push(x);
		} M[r] = cur;
	}
	auto ans = SMP();
	cout << ans << endl;
}
