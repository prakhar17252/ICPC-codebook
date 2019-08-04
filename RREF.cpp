// Running time: O(n^3)
// INPUT:  a[][] = an nxm matrix, n var, m eqn
//         b[] = an nx1 matrix, val of eqn
// OUTPUT: rref[][] = nxm matrix (stored in a[][])
//         returns rank of a[][]

// (m - rank) : arbitrary variables

#define F Fraction
struct F {
  int n, d;
  F(int num = 0, int den = 1) : n(num), d(den) {}

  F& simplify() {
    int g = __gcd(n, d); n /= g; d /= g;
    if (d < 0) n = -n, d = -d; return *this; }
  F invert() { return F(d, n).simplify(); }
  F operator - () { return F(-d, n).simplify(); }
  F operator + (const F &o) const // Add -, *, /
  { return F(n*o.d + d*o.n, d*o.d).simplify(); }
  F& operator = (const F &o)
  { this->n = o.n; this->d = o.d; return *this; }
  F& operator = (const int o)
  { this->n = o; this->d = 1; return *this; }
  F& operator += (const F &o) // Add -=, *=, /=
  { return *this = *this + o; }
};
ld fabs(F& f) { return fabsl(1.0l * f.n / f.d); }
ostream& operator << (ostream& os, const F &f)
{ return os << "(" << f.n <<"/"<< f.d << ")"; }

const ld EPS = 1e-10; using T = Fraction;
using VT = vector<T>; using VVT = vector<VT>;

// n equations, m variables
int rref(VVT &a, VT &b) {
  assert(a.size() == b.size());
  int n = a.size(), m = a[0].size(), r = 0;
  T det = T(1);   // only in case of square matrix
  for (int c = 0; c < m && r < n; c++) {
    int j = r;
    for (int i = r + 1; i < n; i++)
      if (fabs(a[i][c]) > fabs(a[j][c])) j = i;

    if (fabs(a[j][c]) < EPS) continue;
    if (j != r)
    {swap(a[j],a[r]); swap(b[j], b[r]); det *= -1;}

    // T s = 1.0 / a[r][c];
    T s = a[r][c].invert(); det *= s; b[r] *= s;
    for (int j = 0; j < m; j++) a[r][j] *= s;
    for (int i = 0; i < n; i++) {
      if (i != r) {
        T t = a[i][c]; b[i] -= t * b[r];
        for (int j = 0; j < m; j++)
          a[i][j] -= t * a[r][j];
      }
    } r++;
  }

  for (int i = 0; i < n; i++) det *= a[i][i];
  return r;
}