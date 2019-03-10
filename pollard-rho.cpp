ll mul(ll x, ll y, ll m) {
  if (y == 0) return 0;
  if (y % 2) return (x + mul(x, y-1, m)) % m;
  return mul((x + x) % m, y / 2, m); }

ll power(ll x, ll y, ll m) {
  if (y == 0) return 1LL;
  if (y % 2) return mul(x, power(x, y-1, m), m);
  return power(mul(x, x, m), y/2, m); }

ll pollardRho(ll n) {
  if (n == 1) return 1; if (n % 2 == 0) return 2;
  ll x = rng() % (n - 2) + 2, y = x, d = 1;
  ll c = rng() % (n - 1) + 1;
  while (d == 1) {
    x = (mul(x,x,n)+c) % n; y = (mul(y,y,n)+c) % n;
    y = (mul(y,y,n)+c) % n; d = __gcd(abs(x-y), n);
    if (d == n) return pollardRho(n);
  } return d; }

// Rabin-Miller primality testing algorithm
// deterministic for upto 3e23
// replace a in bases with [2, n-2] for randomized
bool MillerRabin(ll n) {
  if (n < 2 || (n > 2 && !(n % 2))) return false;
  ll d = n - 1, r = 0;
  while (!(d % 2)) d /= 2, r++;
  vector<ll> bases({2, 3, 5, 7, 11, 13, 17, 
                  19, 23, 29, 31, 37});
  for (ll a : bases) {
    if (n - 1 <= a) break;  // 1 < a < n-1
    bool comp = true;
    ll x = power(a, d, n);
    if (x == 1 || x == n-1) continue;
    for (int i = 0; i < r; i++) {
      x = mul(x, x, n);
      if (x == n-1) { comp = false; break; }
    } if (comp) return false; }
  return true; }

map<ll, int> factors;
// Precondition:  factors is an empty map, 
//                n is a positive integer
// Postcondition: factors[p] is the exponent of p
//                in prime factorization of n
void fact(ll n){
  if (n == 1) return;
  if(!MillerRabin(n)){
    ll fac = pollardRho(n); fact(n/fac); fact(fac);
  } else factors[n]++;
}
