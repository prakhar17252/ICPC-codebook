const int N = 1e5 + 10, K = 25; 	// log2(N)
int st[N][K+1], n, a[N];				// 0 based
void build() {
	for(int i = 0; i < n; i++)
		st[i][0] = a[i];

	for(int j = 1; j <= K; j++) 
		for(int i = 0; i + (1 << j) - 1 < n; i++)
			st[i][j] = min(st[i][j-1], 
													st[i+(1<<(j-1))][j-1]);
}

int query(int l, int r) {		// RMQ, GCD 
	int j = log2(r-l+1);
	return min(st[l][j], st[r-(1<<j)+1][j]);
}
