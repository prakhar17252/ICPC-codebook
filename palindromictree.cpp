// int b[2] = {31, 29}, m[2] = {1e9+9, 1e9+7};

struct PalindromicTree {
  struct node {
    int next[26] = {0};
    int len = 0; int s_link = 0;
    int occ = 0; int endpos = -1;
    // string str; int h[2] = {0};
  };
// next[i]: palindrome after adding i to both sides
// len:len of palin, h:hash of palin, str:debug str
// s_link: longest proper suffix palindrome

  // [3, num] denote the different palindromes
  PalindromicTree(string s) : s(s) {
    tree.resize(s.size() + 5); num = 2; suff = 2;
    tree[1].len = -1; tree[1].s_link = 1;
    tree[2].len = 0; tree[2].s_link = 1;
    for (int i = 0; i < len(s); i++) addLetter(i);

    for (int i = num; i > 2; i--)
      tree[tree[i].s_link].occ += tree[i].occ;
  }

  string s; vector<node> tree;
  int num, suff;

  // Returns true if new unique palindrome found
  bool addLetter(int pos) {
    int cur = suff, curlen = 0, let = s[pos] - 'a';

    while (true) {
      curlen = tree[cur].len;
      if(pos-1-curlen>=0&&s[pos-1-curlen]==s[pos])
        break;
      cur = tree[cur].s_link;
    }

    if (tree[cur].next[let])
    { suff = tree[cur].next[let]; tree[suff].occ++;
      return false; }

    suff = ++num; tree[num].len = tree[cur].len+2;
    tree[num].occ++; tree[num].endpos = pos;
    tree[cur].next[let] = num;

    if (tree[num].len == 1) {
      tree[num].s_link = 2;
      // tree[num].h[i] = let + 1;
      // tree[num].str += s[pos];
      return true;
    }

    // tree[num].h[i] = ((let + 1) +
    // (let+1)*power(b[i], tree[num].len-1, m[i]) +
    //          tree[cur].h[i] * b[i]) % m[i];

    // tree[num].str = s[pos]+tree[cur].str+s[pos];

    while (true) {
      cur=tree[cur].s_link; curlen=tree[cur].len;
      if(pos-1-curlen>=0&&s[pos-1-curlen]==s[pos])
      {tree[num].s_link=tree[cur].next[let];break;}
    }
    return true;
  }
};
