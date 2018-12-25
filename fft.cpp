const ld pi = acos(-1);
auto FFT = [](vector<ld> a, vector<ld> b){
  auto DFT = [](vector<complex<ld>>&a, bool inv){
    int L=31-__builtin_clz(len(a)), n = 1 << L;
    vector<complex<ld>> A(n);
    for(int k = 0, r, i; k < n; A[r] = a[k++]) 
      for(i = r = 0; i < L; (r<<=1) |= (k>>i++)&1);
    complex<ld> w, wm, t;
    for(int m = 2, j, k; m <= n; m <<= 1) {
      w = {0, 2*pi/m}, wm = exp(inv ? -w : w);
      for(k = 0; k < n; k += m)
        for(j = 0, w = 1; j < m/2; ++j , w *= wm){
          t = w * A[k+j+m/2]; 
          A[k+j+m/2] = A[k+j]-t; A[k+j] += t;
        }
    }
    return A;
  };  
  int n = 4<<31-__builtin_clz(max(len(a),len(b)));
  vector<complex<ld>> A(n), B(n), CC(n);
  for(int i = 0; i < n; ++i) 
    A[i] = i<len(a)?a[i]:0, B[i] = i<len(b)?b[i]:0;
  vector<complex<ld>> AA = DFT(A,0), BB = DFT(B,0);
  for(int i = 0; i < n; ++i) CC[i] = AA[i]*BB[i];
  vector<ld> c;
  for(auto i:DFT(CC,1)) if(len(c)<len(a)+len(b)-1)
    c.pb(i.real()/n+1e-5);
  return c;
};
