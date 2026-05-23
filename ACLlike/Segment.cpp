#include <bits/stdc++.h>
using namespace std;

/*
Segment Tree

配列の区間に対して、最小値・最大値・和・gcd などを O(log N) で取得する。
値の1点更新も O(log N)。

op は区間の値をどう合成するか、e は空区間の値。
*/

int ceil_pow2_segment_tree(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

template <class S, S (*op)(S, S), S (*e)()>
struct SegmentTree {
    int _n, size, log;
    vector<S> d;

    SegmentTree() : SegmentTree(0) {}
    explicit SegmentTree(int n) : SegmentTree(vector<S>(n, e())) {}
    explicit SegmentTree(const vector<S>& v) : _n((int)v.size()) {
        log = ceil_pow2_segment_tree(_n);
        size = 1 << log;
        d.assign(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) update(i);
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const {
        return d[1];
    }

    template <class F>
    int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while ((l & 1) == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = 2 * l;
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <class F>
    int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r & 1)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = 2 * r + 1;
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

   private:
    void update(int k) {
        d[k] = op(d[2 * k], d[2 * k + 1]);
    }
};

/*
使用例1: 区間最小値(RMQ)・1点更新
int op(int a, int b) { return min(a, b); }
int e() { return (int)1e9; }

SegmentTree<int, op, e> seg(a);
seg.set(i, x);
cout << seg.prod(l, r) << "\n";  // min(a[l], ..., a[r-1])


使用例2: 区間最大値
int op(int a, int b) { return max(a, b); }
int e() { return -(int)1e9; }

SegmentTree<int, op, e> seg(a);
cout << seg.prod(l, r) << "\n";  // max(a[l], ..., a[r-1])


使用例3: 区間和・1点更新
long long op(long long a, long long b) { return a + b; }
long long e() { return 0; }

SegmentTree<long long, op, e> seg(a);
seg.set(i, x);
cout << seg.prod(l, r) << "\n";


使用例4: 区間 gcd
long long op(long long a, long long b) { return gcd(a, b); }
long long e() { return 0; }

SegmentTree<long long, op, e> seg(a);
cout << seg.prod(l, r) << "\n";


使用例5: 区間最大値とその位置
using S = pair<int, int>;  // {値, -index}
S op(S a, S b) { return max(a, b); }
S e() { return {numeric_limits<int>::min(), numeric_limits<int>::min()}; }

vector<S> v(n);
for (int i = 0; i < n; i++) v[i] = {a[i], -i};
SegmentTree<S, op, e> seg(v);
auto [mx, neg_i] = seg.prod(l, r);
cout << mx << " " << -neg_i << "\n";  // 最大値と最小 index


使用例6: prefix の lower_bound
// a[i] >= 0 のとき、a[0] + ... + a[r-1] >= x となる最小の r を探す。
// 存在しなければ n。要素の index がほしいなら r - 1。x > 0 とする。
long long op(long long a, long long b) { return a + b; }
long long e() { return 0; }

SegmentTree<long long, op, e> seg(a);
int r = seg.max_right(0, [&](long long s) { return s < x; });
*/
