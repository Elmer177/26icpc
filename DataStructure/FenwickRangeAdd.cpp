#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <class T>
struct FenwickTree {
    int n;
    vector<T> bit;

    FenwickTree(int n_) : n(n_), bit(n_ + 1, 0) {}

    void add(int p, T x) {
        for (int i = p + 1; i <= n; i += i & -i) bit[i] += x;
    }

    T sum_prefix(int r) const {
        T ret = 0;
        for (int i = r; i > 0; i -= i & -i) ret += bit[i];
        return ret;
    }

    T sum(int l, int r) const {
        return sum_prefix(r) - sum_prefix(l);
    }
};

/*
区間加算・区間和

Fenwick Treeを2本使って、次の操作を O(log N) で行う。
- add(l, r, x): [l, r) に x を加算
- sum(l, r): [l, r) の和

区間最小/最大が必要なら Lazy Segment Tree を使う。
*/
struct RangeAddRangeSum {
    int n;
    FenwickTree<ll> bit0, bit1;

    RangeAddRangeSum(int n_) : n(n_), bit0(n_ + 1), bit1(n_ + 1) {}

    void add_prefix(int i, ll x0, ll x1) {
        bit0.add(i, x0);
        bit1.add(i, x1);
    }

    void add(int l, int r, ll x) {
        add_prefix(l, -x * l, x);
        add_prefix(r, x * r, -x);
    }

    ll prefix_sum(int r) {
        return bit0.sum(0, r) + bit1.sum(0, r) * r;
    }

    ll sum(int l, int r) {
        return prefix_sum(r) - prefix_sum(l);
    }
};

/*
使用例:
RangeAddRangeSum bit(5);
bit.add(1, 4, 10); // {0,10,10,10,0}
bit.add(2, 5, 1);  // {0,10,11,11,1}
cout << bit.sum(0, 5) << "\n"; // 33
cout << bit.sum(2, 3) << "\n"; // 11
*/
