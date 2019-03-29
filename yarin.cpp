// N = 1e8 -> (343 ms, 12MB), 1e7 -> (15 ms, 1.2MB)
const int N = 100000000; bitset<N+1> prime;
prime.set(); prime[0] = prime[1] = 0;
for (int i = 4; i <= N; i += 2) prime[i] = 0;

for (int i = 3; i*i <= N; i += 2) if (prime[i])
  for (int j = i*i; j <= N; j += i+i) prime[j] = 0;
