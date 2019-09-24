// int b[2] = {31, 29}, m[2] = {1e9+9,1e9+11};

struct PalindromicTree {
  struct node {
    int next[26] = {0};
    int len = 0; int sufflink = 0;
    int occ = 0; int endpos = -1;
    // string str; int h[2] = {0};
  };

  // [3, num] denote the different palindromes
  PalindromicTree(string s) : s(s) {
    tree.resize(s.size() + 5); num = 2; suff = 2;
    tree[1].len = -1; tree[1].sufflink = 1;
    tree[2].len = 0; tree[2].sufflink = 1;
    for (int i = 0; i < len(s); i++) addLetter(i);

    for (int i = num; i > 2; i--)
      tree[tree[i].sufflink].occ += tree[i].occ;
  }

  string s; vector<node> tree;
  int num, suff;

  // Returns true if new distinct palindrome
  // formed by adding this letter
  bool addLetter(int pos) {
    int cur = suff, curlen = 0, let = s[pos] - 'a';

    while (true) {
      curlen = tree[cur].len;
      if(pos-1-curlen>=0&&s[pos-1-curlen]==s[pos])
        break;
      cur = tree[cur].sufflink;
    }

    if (tree[cur].next[let])
    { suff = tree[cur].next[let]; tree[suff].occ++;
      return false; }

    suff = ++num; tree[num].len = tree[cur].len+2;
    tree[num].occ++; tree[num].endpos = pos;
    tree[cur].next[let] = num;

    if (tree[num].len == 1) {
      tree[num].sufflink = 2;
      // tree[num].h[i] = let + 1;
      // tree[num].str += s[pos];
      return true;
    }

    // tree[num].h[i] = ((let + 1) +
    // (let+1)*power(b[i], tree[num].len-1, m[i]) +
    //          tree[cur].h[i] * b[i]) % m[i];

    // tree[num].str = s[pos]+tree[cur].str+s[pos];

    while (true) {
      cur=tree[cur].sufflink; curlen=tree[cur].len;
      if(pos-1-curlen>=0&&s[pos-1-curlen]==s[pos])
      tree[num].sufflink=tree[cur].next[let];break;
    }
    return true;
  }
};
