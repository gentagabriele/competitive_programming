template<typename T>
struct fenwick_tree {
  int sz, k;
  vector<T> bit;
  fenwick_tree(int n) {
    sz = n + 1;
    k = 1 << (31 - __builtin_clz(n));
    bit.assign(sz, 0);
  }
  fenwick_tree(const vector<T> &v) : fenwick_tree(v.size()) {
    for (int i = 1; i < sz; i++) {
      bit[i] += v[i - 1];
      int j = i + (i & -i);
      if (j < sz) {
        bit[j] += bit[i];
      }
    }
  }
  void add(int idx, T x) {
    while (idx < sz) {
      bit[idx] += x;
      idx += idx & -idx;
    }
  }
  void update(int idx, T x) {
    add(idx, x - range(idx, idx));
  }
  T sum(int idx) const {
    T res = 0;
    while (idx > 0) {
      res += bit[idx];
      idx -= idx & -idx;
    }
    return res;
  }
  T range(int lft, int rgt) const {
    return sum(rgt) - sum(lft - 1);
  }
  int lower_bound(T x) const {
    int idx = 0;
    for (int j = k; j > 0; j >>= 1) {
      if (idx + j < sz && x > bit[idx + j]) {
        x -= bit[idx + j];
        idx += j;
      }
    }
    return idx + 1;
  }
};
