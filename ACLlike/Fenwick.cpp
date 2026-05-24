#include <bits/stdc++.h>
using namespace std;

/*
Fenwick Tree / Binary Indexed Tree

配列に対して、1点加算と区間和を O(log N) で処理する。
値の更新があり、累積和を何度も取りたいときに使う。

- add(p, x): a[p] に x を足す
- sum(l, r): a[l] + ... + a[r-1] を返す
*/

template <class T>
struct FenwickTree {
    int _n;
    vector<T> data;

    FenwickTree() : _n(0) {}
    explicit FenwickTree(int n) : _n(n), data(n, 0) {}

    void add(int p, T x) {
        assert(0 <= p && p < _n);
        for (p++; p <= _n; p += p & -p) data[p - 1] += x;
    }

    T sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        return sum_prefix(r) - sum_prefix(l);
    }

   private:
    T sum_prefix(int r) const {
        T s = 0;
        for (; r > 0; r -= r & -r) s += data[r - 1];
        return s;
    }
};

/*
使用例:
FenwickTree<long long> fw(n);
fw.add(i, x);
cout << fw.sum(l, r) << "\n";
*/
