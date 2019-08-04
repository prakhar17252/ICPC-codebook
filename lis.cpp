// Given a list of numbers of length n, this 
// returns the longest increasing subsequence.
//
// Running time: O(n log n)
//
//   INPUT: a vector of integers
//   OUTPUT: a vector containing the LIS

#define STRICTLY_INCREASNG

vll LongestIncreasingSubsequence(vll v) {
  vpll best; vll dad(v.size(), -1);

  for (int i = 0; i < v.size(); i++) {
#ifdef STRICTLY_INCREASNG
    pll item = mp(v[i], 0);
    auto it = lower_bound(all(best), item);
    item.ss = i;
#else
    pll item = mp(v[i], i);
    auto it = upper_bound(all(best), item);
#endif
    if (it == best.end()) {
      dad[i] = best.empty() ? -1 : best.back().ss;
      best.pb(item);
    } else {
      dad[i] = it==best.begin() ? -1:prev(it)->ss;
      *it = item;
    }
  }

  vll ret;
  for (int i = best.back().ss; i >= 0; i = dad[i])
    ret.pb(v[i]);
  reverse(all(ret)); return ret;
}
