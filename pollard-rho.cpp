ull mul_mod(ull a, ull b, ull m){
  ull y = (ull)((ld)a * (ld)b / m + 1.0 / 2) * m;
  ull x = a * b, r = x - y;
  if ((ll) r < 0){
    r = r + m; y = y - 1;
  } return r;
}

ull C, a, b;

ull f(ull a, ull b){
  return (mul_mod(a, a, b) + C) % b; }

ull pollard(ull n){
  if(!(n % 2)) return 2;
  C = 0; ull iter = 0;
  while(iter <= 1000){
    ull x, y, d;
    x = y = 2; d = 1;
    while(d == 1){
      x = f(x, n);
      y = f(f(y, n), n);
      ull m = abs(x-y);
      a = m; b = n; d = gcd(a, b);
    }
    if(d != n) return d;
    iter++; C = rand();
  } return 1;
}

// Rabin-Miller primality testing algorithm
bool isPrime(ull n){
  ull d = n-1, s = 0;
  if(n <=3 || n == 5) return true;
  if(!(n % 2)) return false;
  while(!(d % 2)){ s++; d /= 2; }
  for(ull i = 0; i < 32; i++){
    ull a = rand(); a <<= 32;
    a += rand(); a %= (n-3); a += 2;
    ull x = power(a, d, n);   // make power ull
    if(x == 1 || x == n-1) continue;
    for(ull j = 1; j <= s-1; j++){
        x = mul_mod(x, x, n);
        if(x == 1) return false;
        if(x == n-1) break;
    }
    if(x != n-1) return false;
  } return true;
}

map<ull, int> factors;
// Precondition:  factors is an empty map, 
//                n is a positive integer
// Postcondition: factors[p] is the exponent of p 
//                in prime factorization of n
void fact(ull n){
  if(!isPrime(n)){
    ull fac = pollard(n);
    fact(n/fac); fact(fac);
  } else {
    map<ull,int>::iterator it = factors.find(n);
    if(it != factors.end()) (*it).ss++;
    else factors[n] = 1;
} }
