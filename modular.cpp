// This is a collection of useful code for solving
// problems that involve modular linear equations.
// Note that all of the algorithms described here
// work on nonnegative integers.

// computes lcm(a,b)
int lcm(int a, int b) {
  return (a / __gcd(a,b)) * b;
}

// returns gcd(a,b); finds x,y s.t. d = ax + by
int extended_euclid(int a, int b, int &x, int &y) {
  int xx = y = 0; int yy = x = 1;
  while (b) {
    int q = a/b;
    int t = b; b = a%b; a = t;
    t = xx; xx = x-q*xx; x = t;
    t = yy; yy = y-q*yy; y = t;
  } return a;
}

// finds all solutions to ax = b (mod n)
vll modular_equation_solver(int a, int b, int n){
	vll solutions; int x, y;
	int d = extended_euclid(a, n, x, y);
	if (!(b%d)) {
		x = takemod(x*(b/d), n);
		for (int i = 0; i < d; i++)
			solutions.pb(takemod(x + i*(n/d), n));
	} return solutions;
}

// computes a^-1 (mod n), returns -1 on failure
int mod_inverse(int a, int n) {
	int x, y; int d = extended_euclid(a, n, x, y);
	if (d > 1) return -1;
	return takemod(x, n);
}

// Chinese remainder theorem (special case): find z
// such that z % x = a, z % y = b. Here, z is 
// unique modulo M = lcm(x,y).
// Return (z,M). On failure, M = -1.
pii CRT(int a1, int n1, int a2, int n2) {
	int x, y; int d = extended_euclid(n1, n2, x, y);
	int l = (n1 * n2) / d, A = (a2-a1);
	if(A % d != 0) return mp(0, -1);
	return mp(takemod(a1+(x*A/d%(n2/d))*n1, l), l);
}

// Chinese remainder theorem: find z such that
// z % x[i] = a[i] for all i. Solution is
// unique mod M = lcm_i (x[i]). Return (z,M). On
// failure, M = -1. Note that we do not require 
// the a[i]'s to be relatively prime.
pii CRT(const vll &x, const vll &a) {
	pii ret = mp(a[0], x[0]);
	for (int i = 1; i < x.size(); i++) {
		ret = CRT(ret.ff, ret.ss, a[i], x[i]);
		if (ret.ss == -1) break;
	} return ret;
}

// computes x and y such that ax + by = c; 
// on failure returns false. g is gcd(a, b)
// int qa = b / g, qb = b / g;
// X = x + k * qa, Y = y - k * qb are also 
// solutions of equation where k is any integer
bool linear_diophantine(int a, int b, int c, 
											int& x0, int& y0, int& g) {
	g = extended_euclid(abs(a), abs(b), x0, y0);
	if(c % g != 0) return false;
	x0 *= c / g; y0 *= c / g;
	if(a < 0) x0 *= -1; if(b < 0) y0 *= -1;
	assert(a * x0 + b * y0 == c);
	return true;
}
