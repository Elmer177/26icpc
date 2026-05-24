#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
imos法

区間加算をたくさん受け取って、最後に全点の値を一度だけ復元する。
途中で区間和や一点取得を何度も聞かれる場合は Fenwick / Lazy Segment Tree を使う。

add の区間は半開区間 [l, r)。
1D: add O(1), build O(N)
2D: add O(1), build O(HW)
*/

// 一次元imos: [l, r) に x を加算
template <class T>
struct Imos1D {
    int n;
    vector<T> diff;

    Imos1D(int n_) : n(n_), diff(n_ + 1, 0) {}

    void add(int l, int r, T x) {
        diff[l] += x;
        diff[r] -= x;
    }

    vector<T> build() {
        vector<T> a(n);
        T cur = 0;
        for (int i = 0; i < n; i++) {
            cur += diff[i];
            a[i] = cur;
        }
        return a;
    }
};

/*
使用例:
Imos1D<ll> imos(5);
imos.add(1, 4, 10); // a[1],a[2],a[3] に +10
imos.add(2, 5, 1);  // a[2],a[3],a[4] に +1
vector<ll> a = imos.build(); // {0,10,11,11,1}

Imos2D<ll> imos2(3, 4);
imos2.add(0, 2, 1, 4, 1); // 上2行、1列目から3列目まで +1
auto grid = imos2.build();
*/

// 二次元imos: [u, d) x [l, r) に x を加算
template <class T>
struct Imos2D {
    int h, w;
    vector<vector<T>> diff;

    Imos2D(int h_, int w_) : h(h_), w(w_), diff(h_ + 1, vector<T>(w_ + 1, 0)) {}

    void add(int u, int d, int l, int r, T x) {
        diff[u][l] += x;
        diff[d][l] -= x;
        diff[u][r] -= x;
        diff[d][r] += x;
    }

    vector<vector<T>> build() {
        for (int i = 0; i <= h; i++) {
            for (int j = 0; j < w; j++) diff[i][j + 1] += diff[i][j];
        }
        for (int i = 0; i < h; i++) {
            for (int j = 0; j <= w; j++) diff[i + 1][j] += diff[i][j];
        }
        vector<vector<T>> a(h, vector<T>(w));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) a[i][j] = diff[i][j];
        }
        return a;
    }
};
