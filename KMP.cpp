void findwin(string pat, int n, int win[]){
	int s = 0, i = 1; win[s] = 0;
	while(i < n){
		if(pat[i] == pat[s]){
			s++; win[i++] = s;
		} else {
			if(s != 0) s = win[s-1];
			else win[i++] = 0;
}	} }

bool kmpsearch(string full, string pat){
	int n = full.size(), m = pat.size();
	int win[m]; findwin(pat, m, win);
	int i = 0, j = 0;
	while(i < n) {
		if(pat[j] == full[i]){
			j++; i++;
		} if(j == m) {
			// match found at i-j
			j = win[j-1];
		} else if (i < n && pat[j] != full[i]){
			if(j!= 0) j = win[j-1];
			else i++;
		}
	} return false;
}
