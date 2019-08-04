const int N = 1e5 + 10; bool prime[N];
int mu[N]; vector<int> divs[N]; bool sqf[N];

void computemobius() {
  for(int i = 1; i < N; i++)
    for(int j = i; j < N; j+=i)
      divs[j].pb(i);

  for(int i = 1; i < N; i++) prime[i] = true;
  prime[0] = prime[1] = false;
  for(int i = 2; i < N; i++) if(prime[i]) {
    for(int j = 2*i; j < N; j += i)
      prime[j] = false;
  }

  for(int i = 2; i * i < N; i++) {
    for(int j = i * i; j < N; j += i * i)
      sqf[j] = true;
  }

  for(int i = 1; i < N; i++) {
    if(sqf[i]) { mu[i] = 0; continue; }
    int p = 0;
    for (int j : divs[i]) p ^= prime[j];

    if(p) mu[i] = -1;
    else mu[i] = 1;
  }
}