// This is the famous "Yarin sieve", 
// for use when memory is tight.
#define MAXSIEVE 100000000 // Primes till this
#define MAXSIEVEHALF (MAXSIEVE/2)
#define MAXSQRT 5000 // sqrt(MAXSIEVE)/2
char a[MAXSIEVE/16+2];
bool isprime(int n)
{return n==2 || (n&1 && a[n>>4]&(1<<((n>>1)&7))); }

memset(a, 255, sizeof(a));
a[0] = 0xFE;
for(int i = 1; i < MAXSQRT; i++)
	if(a[i >> 3] && (1 << (i & 7)))
		for(int j = 3*i+1; j<MAXSIEVEHALF; j += 2*i+1)
			a[j>>3] &= ~(1 << (j & 7));
