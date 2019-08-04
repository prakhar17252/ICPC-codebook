// Maximal palindrome lengths centered around each
// position in a string(incl. positions between
// characters) and returns them in left-to-right
// order of centres. Linear time.
// Ex: "opposes" ->
// [0, 1, 0, 1, 4, 1, 0, 1, 0, 1, 0, 3, 0, 1, 0]
vector<int> fastLongestPalindromes(string str) {
  int i = 0, j, d, s, e, lLen, palLen=0;
  vector<int> res;
  while(i < len(str)) {
    if(i > palLen && str[i-palLen-1] == str[i]) {
      palLen += 2; i++; continue;
    }
    res.pb(palLen); s = len(res) - 2, e = s-palLen;
    bool b = true;
    for(j = s; j > e; j--) {
      d = j - e - 1;
      if(res[j] == d){palLen = d; b = 0; break;}
      res.pb(min(d, res[j]));
    }
    if(b){ palLen = 1; i++; }
  }
  res.pb(palLen); lLen = len(res);
  s = lLen-2; e = s-(2 * len(str) + 1 - lLen);
  for(i = s; i > e; i--) {
    d = i-e-1; res.pb(min(d, res[i])); }
  return res;}
