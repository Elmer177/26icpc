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
転倒数

i < j かつ a[i] > a[j] である組 (i,j) の個数。
隣接swapで配列を昇順にする最小回数にも等しい。

値が大きい場合や負の場合も、内部で座標圧縮して数える。
計算量 O(N log N)。
*/
template <class T>
ll inversion_number(vector<T> a) {
    vector<T> xs = a;
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    FenwickTree<ll> fw((int)xs.size());
    ll inv = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        int x = lower_bound(xs.begin(), xs.end(), a[i]) - xs.begin();
        inv += i - fw.sum(0, x + 1);
        fw.add(x, 1);
    }
    return inv;
}

/*
使用例:
vector<int> a = {3, 1, 2};
cout << inversion_number(a) << "\n"; // 2: (3,1), (3,2)
*/
