struct BIT {
  vector<int> bit;        // 1 based elements
  int n, k;
  BIT(int n) : n(n), bit(n+1), k(ceil(log2(n))) {}

  void add(int i, int val) { // update a[i] += val
		while(i <= n) {
			bit[i] += val; i += (i & -i);
	} }

  int get(int i) {			// sum of a[1] .... a[i]
		int sum = 0;
		while(i > 0) {
			sum += bit[i]; i -= (i & -i);
		} return sum;
  }

	// sum of a[l] .... a[r] (both inclusive)
  int get(int l, int r){ return get(r)-get(l-1); }

  void build(vector<int> &a, int n) {
		for(int i = 1; i <= n; i++) add(i, a[i]);
  }

  int lower_bound(int v) {
		int sum = 0, pos = 0;
		for(int i = k; i >= 0; i--) {
			int pw = (1 << i);
			// bit[pos + pw] <= v for upper_bound
			if(pos + pw <= n && sum + bit[pos + pw] < v)
				sum += bit[pos += pw];
		} return pos + 1; 
  }
};
