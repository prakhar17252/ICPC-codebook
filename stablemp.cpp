// Gale-Shapley algorithm for stable marriage
// madj[i][j] is jth highest ranked woman for man i
// fpref[i][j] is the rank woman i assigns to man j
// Returns a pair of vectors (mpart, fpart), where
// mpart[i] gives partner of man i & fpart of woman
vector<vll> madj, fpref;
pair<vll, vll> stable_marriage() {
	int n = madj.size();
	vll mpart(n, -1), fpart(n, -1), midx(n);
	queue<int> mfree;
	for (int i = 0; i < n; i++) mfree.push(i);
	while (!mfree.empty()) {
		int m = mfree.front(); mfree.pop();
		int f = madj[m][midx[m]++];
		if (fpart[f] == -1) {
			mpart[m] = f; fpart[f] = m;
		} else if (fpref[f][m] < fpref[f][fpart[f]]) {
			mpart[fpart[f]] = -1; mfree.push(fpart[f]);
			mpart[m] = f; fpart[f] = m;
		} else {
			mfree.push(m);
		}
	}	return mp(mpart, fpart);
}
