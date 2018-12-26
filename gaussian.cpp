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

const double EPS = 1e-10;
typedef double ld;
typedef vector<ld> VT;
typedef vector<VT> VVT;

ld GaussJordan(VVT &a, VVT &b) {
  int n = a.size(), m = b[0].size();
  vll irow(n), icol(n), ipiv(n);
  ld det = 1;

  for(int i = 0; i < n; i++) {
    int pj = -1, pk = -1;
    for(int j = 0; j < n; j++) if(!ipiv[j])
      for(int k = 0; k < n; k++) if(!ipiv[k])
        if(pj==-1 || fabs(a[j][k])>fabs(a[pj][pk]))
        { pj = j; pk = k; }

    if(fabs(a[pj][pk]) < EPS) return 0; // singular
    ipiv[pk]++;
    swap(a[pj], a[pk]); swap(b[pj], b[pk]);
    
    if(pj != pk) det *= -1;
    irow[i] = pj; icol[i] = pk;

    ld c = 1.0 / a[pk][pk]; det *= a[pk][pk];
    a[pk][pk] = 1.0;
    for(int p = 0; p < n; p++) a[pk][p] *= c;
    for(int p = 0; p < m; p++) b[pk][p] *= c;
    for(int p = 0; p < n; p++) if(p != pk) {
      c = a[p][pk];
      a[p][pk] = 0;
      int q;
      for(q = 0; q < n; q++) a[p][q] -= a[pk][q]*c;
      for(q = 0; q < m; q++) b[p][q] -= b[pk][q]*c;      
    }
  }

  for(int p = n-1; p >= 0; p--) 
    if(irow[p] != icol[p]) 
      for(int k = 0; k < n; k++) 
        swap(a[k][irow[p]], a[k][icol[p]]);
  return det;
}
