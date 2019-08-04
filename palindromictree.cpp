const int MAXN = 105000;

struct node {
  int nxt[26], len, suflink, num;
};

int len; string s; node tree[MAXN];
// node 1: root of len -1, node 2: root of len 0
int num;
int suff;           // max suffix palindrome
ll ans;

bool addLetter(int pos) {
  int cur = suff, curlen = 0;
  int let = s[pos] - 'a';

  while (true) {
    curlen = tree[cur].len;
    if(pos-curlen > 0 && s[pos-1-curlen] == s[pos])
      break;
    cur = tree[cur].suflink;
  }
  if(tree[cur].nxt[let]) {
    suff = tree[cur].nxt[let]; return false;
  }
  suff = ++num;
  tree[num].len = tree[cur].len + 2;
  tree[cur].nxt[let] = num;

  if(tree[num].len == 1) {
    tree[num].suflink = 2; tree[num].num = 1;
    return true;
  }
  while(true){
    cur = tree[cur].suflink;
    curlen = tree[cur].len;
    if(pos-curlen > 0 && s[pos-1-curlen]==s[pos]){
      tree[num].suflink=tree[cur].nxt[let]; break;
    }
  }
  tree[num].num = 1 + tree[tree[num].suflink].num;
  return true;
}

void initTree() {
  num = 2; suff = 2;
  tree[1].len = -1; tree[1].suflink = 1;
  tree[2].len = 0; tree[2].suflink = 1;
}

int main() {
  cin >> s;
  len = s.size();
  initTree();

  for (int i = 0; i < len; i++)
  { addLetter(i); ans += tree[suff].num; }

  cout << ans << endl;
  return 0;
}
