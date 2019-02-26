using cd = complex<ld>;
const ld PI = acos(-1);

void FFT(vector<cd> &a, bool invert) {
  int n = a.size();
  for(int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for(; j & bit; bit >>= 1) j ^= bit;
    j ^= bit;
    if(i < j) swap(a[i], a[j]);
  }

  for(int len = 2; len <= n; len <<= 1) {
    ld ang = 2 * PI / len * (invert ? -1 : 1);
    cd wlen(cos(ang), sin(ang));
    for(int i = 0; i < n; i += len) {
      cd w(1);
      for(int j = 0; j < len / 2; j++) {
        cd u = a[i+j], v = a[i+j+len/2] * w;
        a[i+j] = u + v; a[i+j+len/2] = u - v;
        w *= wlen;
  } } }

  if(invert) for(cd &x : a) x /= n;
}

vll multiply(vll const& a, vll const& b) {
  vector<cd> fa(all(a)), fb(all(b));
  int n = 1;
  while(n < a.size() + b.size()) n <<= 1;
  fa.resize(n); fb.resize(n); vll res(n);

  FFT(fa, false); FFT(fb, false); // FFT
  for(int i = 0; i < n; i++) fa[i] *= fb[i];
  FFT(fa, true); // Inverse FFT

  for(int i = 0; i < n; i++) 
    res[i] = round(fa[i].real());
  return res;
}
