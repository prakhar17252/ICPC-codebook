// Gauss-Jordan elimination with full pivoting.
// Uses:
//   (1) solving systems of linear equations (AX=B)
//   (2) inverting matrices (AX=I)
//   (3) computing determinants of square matrices
// Running time: O(n^3)
// INPUT:  a[][] = an nxn matrix
//         b[][] = an nxm matrix
//         A MUST BE INVERTIBLE!
//
// OUTPUT: X      = an nxm matrix (stored in b[][])
//         A^{-1} = an nxn matrix (stored in a[][])
//         returns determinant of a[][]

#define F Fraction
struct F {
  int n, d;
  F(int num = 0, int den = 1) : n(num), d(den) {}

  F& simplify() {
    int g = __gcd(n, d); n /= g; d /= g;
    if (d < 0) n = -n, d = -d; return *this; }
  F invert() { return F(d, n).simplify(); }
  ld abs() { return fabs(1.0 * n / d); }
  F operator - () { return F(-d, n).simplify(); }
  F operator + (const F &o) const // Add -, *, /
  { return F(n*o.d + d*o.n, d*o.d).simplify(); }
  F& operator = (const F &o)
  { this->n = o.n; this->d = o.d; return *this; }
  F& operator = (const int o)
  { this->n = o; this->d = 1; return *this; }
  F& operator += (const F &o) // Add -=, *=, /=
  { *this = *this + o; return *this; }
};
ostream& operator << (ostream& os, const F &f)
{ return os << "(" << f.n <<"/"<< f.d << ")"; }

const ld EPS = 1e-10; using T = Fraction;
using VT = vector<T>; using VVT = vector<VT>;

T GaussJordan(VVT &a, VVT &b) { 
  int n = a.size(), m = b[0].size(), q;
  vll irow(n), icol(n), ipiv(n); T det = T(1);

  for(int i = 0; i < n; i++) {
    int pj = -1, pk = -1;
    for(int j = 0; j < n; j++) if(!ipiv[j])
      for(int k = 0; k < n; k++) if(!ipiv[k])
        if(pj==-1 || fabs(a[j][k])>fabs(a[pj][pk]))
        { pj = j; pk = k; }
    // change fabs for Fraction
    if(fabs(a[pj][pk])<EPS) return T(0); //singular
    ipiv[pk]++;
    swap(a[pj], a[pk]); swap(b[pj], b[pk]);
    
    if(pj != pk) det *= T(-1);
    irow[i] = pj; icol[i] = pk;

    T c = 1.0 / a[pk][pk]; //c = a[pk][pk].invert()
    det *= a[pk][pk]; a[pk][pk] = T(1);
    for(int p = 0; p < n; p++) a[pk][p] *= c;
    for(int p = 0; p < m; p++) b[pk][p] *= c;
    for(int p = 0; p < n; p++) if(p != pk) {
      c = a[p][pk]; a[p][pk] = T(0);
      for(q = 0; q < n; q++) a[p][q] -= a[pk][q]*c;
      for(q = 0; q < m; q++) b[p][q] -= b[pk][q]*c;      
  } }

  for(int p = n-1; p >= 0; p--) 
    if(irow[p] != icol[p]) 
      for(int k = 0; k < n; k++) 
        swap(a[k][irow[p]], a[k][icol[p]]);
  return det; }
