const int N = 1e5 + 10;
int z[N], p[N];

//z[i] : longest common prefix(lcp) of s and s[i..]
void zfunction(string s) {
	int l = 0, r = 0, n = len(s); z[0] = 0;
	for (int i = 1; i < n; i++) {
		if (i <= r) z[i] = min(z[i-l], r - i + 1);
		while(z[i]+i < n && s[z[i]]==s[z[i]+i])	z[i]++;
		if (z[i] + i - 1 > r) { l = i; r = z[i]+i-1; } 
} }

//p[i] : pref of s[0...i] that is also its suffix
void prefixfunction(string s) {
	p[0] = 0; int n = len(s);
	for(int i = 1; i < n; i++) {
		int j = p[i-1];
		while(j > 0 && s[j] != s[i]) j = p[j-1];
		if(s[j] == s[i]) p[i] = j+1;
} }

// Returns all positions where match is found
vector<int> kmpsearch(string text, string pat) {
	int n = len(text), m = len(pat), i = 0, j = 0;
	prefixfunction(pat); vector<int> res;
	while (i < n) {
		if (pat[j] == text[i]) { j++; i++; } 
		if (j == m) { res.pb(i - j); j = p[j-1]; } 
    else if (i < n && pat[j] != text[i]) {
			if (j != 0) j = p[j-1];
			else i++;
  } } return res;
}
