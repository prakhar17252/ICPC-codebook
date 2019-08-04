const int N = 1000, M = 1000;
int BIT[N+1][M+1], a[N+1][M+1];
int n, m;   // 1 <= x <= n, 1 <= y <= m

// Add val to cell (x, y)
void update(int x, int y, int val){
  for(int x1 = x; x1 <= n; x1 += (x1 & -x1))
    for(int y1 = y; y1 <= m; y1 += (y1 & -y1))
      BIT[x1][y1] += val;
}

// Get sum of (1, 1) to (x, y)
int sum(int x, int y){
  int sum = 0;
  for(int x1 = x; x1 > 0; x1 -= (x1 & -x1))
    for(int y1 = y; y1 > 0; y1 -= (y1 & -y1))
    	sum += BIT[x1][y1];
	return sum;
}

// Get sum of rectangle with lower left cell
// (x1, y1) to upper right cell (x2, y2)
int sum(int x1, int y1, int x2, int y2){
	return sum(x2, y2) - sum(x2, y1-1) -
         sum(x1-1, y2) + sum(x1-1, y1-1);
}