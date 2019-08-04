// Suffix array construction in O(L log^2 L) time.
// Routine for computing the length of longest 
// common prefix of two suffixes in O(log L) time.
// INPUT: string s
// OUTPUT: array suffix[] such that 
//         suffix[i] = index (from 0 to L-1) of 
//         substring s[i...L-1] in list of sorted 
//         suffixes. That is, if we take inverse 
//         of the permutation suffix[],
//         we get the actual suffix array.

// bobocel is the 0'th suffix in sorted order
//  obocel is the 5'th suffix in sorted order
//   bocel is the 1'st suffix in sorted order
// SuffixArray suffix("bobocel");
// vector<int> v = suffix.GetSuffixArray();
// Expected v: 0 5 1 6 2 3 4
// int lcp = suffix.LongestCommonPrefix(0, 2);
// Expected lcp: 2

struct SuffixArray {
  const int L;
  string s;
  vector<vector<int> > P;
  vector<pair<pair<int,int>,int> > M;

  SuffixArray(const string &s) : L(len(s)), s(s), 
                    P(1, vector<int>(L, 0)), M(L){
    for(int i = 0; i < L; i++) 
      P[0][i] = L==1 ? i : int(s[i]);

    int skp, lvl;
    for(skp = lvl = 1; skp < L; skp *= 2, lvl++){
      P.pb(vector<int>(L, 0));
      for(int i = 0; i < L; i++) 
        M[i] = {{P[lvl-1][i], (i+skp < L ? 
                  P[lvl-1][i + skp] : -1000)}, i};
      sort(all(M));
      for (int i = 0; i < L; i++) 
      P[lvl][M[i].ss] = ((i && M[i].ff==M[i-1].ff) 
                          ? P[lvl][M[i-1].ss] : i);
    }    
  }

  vector<int> GetSuffixArray() { return P.back(); }

  // returns the length of longest common prefix 
  // of s[i...L-1] and s[j...L-1]
  int LongestCommonPrefix(int i, int j) {
    int len = 0;
    if(i == j) return L - i;
    for(int k = len(P)-1; k>-1 && i<L && j<L; k--){
      if(P[k][i] == P[k][j]) {
        i += 1 << k; j += 1 << k; len += 1 << k;
    } } 
    return len; }
};
