// f is bitonic with a single global maximum
int lo = -1, hi = n;
while (hi - lo > 1) {
	int mid = (hi + lo) / 2;
	if (f(mid) > f(mid + 1)) hi = mid;
	else lo = mid; 
}	//lo + 1 is the answer
