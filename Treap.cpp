template <class T> class treap_set {
private:
  struct item; using pitem = item*;
  pitem root_ = nullptr; mt19937_64 rnd; // init
  struct item {
    ll prior; int cnt, rev;
    T key, lazy, fsum; pitem l, r;

    item(T x, ll p) {
      lazy = 0LL * T(); key = fsum = x; cnt = 1;
      rev = 0; l = r = nullptr; prior = p;
    }
  };

  int cnt(pitem it) { return it ? it->cnt : 0; }

  void upd_cnt(pitem it)
  {if (it) it->cnt = cnt(it->l) + cnt(it->r) + 1;}

  void upd_sum(pitem it) {
    if (!it) return;
    it->fsum = it->key; push(it->l); push(it->r);
    if (it->l) it->fsum = it->fsum + it->l->fsum;
    if (it->r) it->fsum = it->fsum + it->r->fsum;
  }

  void update(pitem t, T lazy, int rev) {
    if (!t) return; t->lazy = t->lazy + lazy;
    t->rev = t->rev ^ rev; t->key = t->key + lazy;
    t->fsum = t->fsum + cnt(t) * lazy;
  }

  void push(pitem t) {
    if (!t) return; update(t->l, t->lazy, t->rev);
    update(t->r, t->lazy, t->rev); t->lazy=0LL*T();
    if (t->rev) { swap(t->l, t->r); } t->rev = 0;
  }

  // merge l and r into t
  void merge(pitem& t, pitem l, pitem r) {
    push(l); push(r);
    if (!l || !r) { t = l ? l : r; }
    else if (l->prior > r->prior)
    { merge(l->r, l->r, r); t = l; }
    else { merge(r->l, l, r->l); t = r; }
    upd_cnt(t); upd_sum(t);
  }

  // split t into l and r by position
  void split(pitem t, pitem& l, pitem& r, int pos){
    if (!t) {return void( l = r = 0 );} push(t);
    if (pos <= cnt(t->l))
    { split(t->l, l, t->l, pos); r = t; }
    else
    { split(t->r, t->r, r, pos-1-cnt(t->l)); l=t; }
    upd_cnt(t); upd_sum(t);
  }

  void insert(pitem& t, pitem it, int pos){push(t);
    if (!t) t = it;
    else if (it->prior > t->prior)
    { split(t, it->l, it->r, pos); t = it; }
    else if (pos<=cnt(t->l)) insert(t->l, it, pos);
    else insert(t->r, it, pos - cnt(t->l) - 1 );
    upd_cnt(t); upd_sum(t);
  }

  void erase(pitem& t, int pos) { push(t);
    if (cnt(t->l) == pos) merge(t, t->l, t->r);
    else if (pos < cnt(t->l)) erase(t->l, pos);
    else erase(t->r, pos - cnt(t->l) - 1 );
    upd_cnt(t); upd_sum(t);
  }

  T get(pitem t, int pos) { push(t);
    if (pos < cnt(t->l)) return get(t->l, pos);
    else if (pos == cnt(t->l)) return t->key;
    return get(t->r, pos - cnt(t->l) - 1);
  }
public:
  // To do something in [l, r], split at
  // pos = r+1 and l, do reqd. operation, and merge
  int size() { return cnt(root_); }

  void insert(int pos, T x) {
    if (pos > size()) return;
    pitem it = new item(x, rnd());
    insert(root_, it, pos);
  }

  void erase(int pos)
  { if (pos >= size()) return; erase(root_, pos); }

  T operator[](int pos) {return get(root_, pos);}
};