const int N = 1e5 + 10;
int z[N], p[N];

void zfunction(string s) {
	int l = 0, r = 0, n = len(s);
	z[0] = 0;
	for(int i = 1; i < n; i++) {
		if(i <= r) z[i] = min(z[i-l], r - i + 1);
		
		while(z[i]+i < n && s[z[i]] == s[z[i]+i])
			z[i]++;
		
		if(z[i] + i - 1 > r) {
			l = i; r = z[i] + i - 1;
} } }

void prefixfunction(string s) {
	p[0] = 0;
	for(int i = 1; i < n; i++) {
		int j = p[i-1];
		while(j > 0 && s[j] != s[i]) j = p[j-1];
		if(s[j] == s[i]) j++;						// emaxx
		p[i] = j;												// emaxx
		// if(s[j] == s[i]) p[i] = j+1;	// Mike notes
} }
