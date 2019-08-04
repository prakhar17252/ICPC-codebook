/*  Returns false if negative cycle detected
    Otherwise function returns true and dist[i]
    is length of shortest path from src to i.
    w[i][j] = weight from i to j.
    prev[i] is used to retrace path from src.
    Running time: O(|V|^3) */
const int N = 100;
int w[N][N], dist[N], prev[N], n;

bool BellmanFord (int src){
  fill(dist, dist+N, inf); reset(prev, -1);
  dist[src] = 0;

  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (dist[j] > dist[i] + w[i][j]){
          if (k == n-1) return false;
          dist[j] = dist[i] + w[i][j];
          prev[j] = i;
        }
  return true;
}
