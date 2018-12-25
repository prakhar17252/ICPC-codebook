/*  Calculates the lCS of two vectors
    Backtracks to find a single subsequence. */
const int N = 1000 + 10;
int A[N], B[N], dp[N][N] = {0}, n, m;
vector<int> res;

void backtrack(int i, int j) {
  if(!i || !j) return;
  if(A[i-1] == B[j-1]) { 
    res.push_back(A[i-1]); backtrack(i-1, j-1); 
  } else {
    if(dp[i][j-1] >= dp[i-1][j]) backtrack(i, j-1);
    else backtrack(i-1, j);
} }

void LCS() {  
  for(int i=1; i<=n; i++)
    for(int j=1; j<=m; j++) {
      if(A[i-1]==B[j-1]) dp[i][j]=dp[i-1][j-1]+1;
      else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    }
  backtrack(n, m); reverse(all(res)); }
