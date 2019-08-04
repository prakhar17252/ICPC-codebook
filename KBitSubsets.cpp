inline int nxt(int v) {
 int t = v | (v - 1);
 return (t+1)|(((~t&-~t)-1)>>(__builtin_ctz(v)+1));
}
// ...
// handle 0 bits separately
for (int k = 1; k <= n; ++k) {
  for (int w = (1<<k)-1; w < (1<<n); w = nxt(w)) {
    // w is mask with k set bits
  }
}