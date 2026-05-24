#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
累積和

同じ配列に対して区間和を何度も聞かれるときに使う。
前計算 O(N) / クエリ O(1)。

区間はすべて半開区間 [l, r)。
AtCoderの問題文が「L番目からR番目まで」(1-indexed, 両端含む) のときは、
0-indexedに直して sum(L-1, R) とすることが多い。
*/

// 一次元累積和: sum(l, r) = a[l] + ... + a[r-1]
template <class T>
struct CumulativeSum1D {
    vector<T> s;

    CumulativeSum1D() = default;
    CumulativeSum1D(const vector<T>& a) { build(a); }

    void build(const vector<T>& a) {
        int n = (int)a.size();
        s.assign(n + 1, 0);
        for (int i = 0; i < n; i++) s[i + 1] = s[i] + a[i];
    }

    T sum(int l, int r) const {
        return s[r] - s[l];
    }
};

/*
使用例:
vector<ll> a = {1, 2, 3, 4, 5};
CumulativeSum1D<ll> cs(a);
cout << cs.sum(1, 4) << "\n"; // 2 + 3 + 4 = 9

vector<vector<ll>> grid = {
    {1, 2, 3},
    {4, 5, 6},
};
CumulativeSum2D<ll> cs2(grid);
cout << cs2.sum(0, 2, 1, 3) << "\n"; // 2列目以降の合計: 2+3+5+6 = 16
*/

// 二次元累積和: sum(u, d, l, r) = [u,d) x [l,r) の和
template <class T>
struct CumulativeSum2D {
    vector<vector<T>> s;

    CumulativeSum2D() = default;
    CumulativeSum2D(const vector<vector<T>>& a) { build(a); }

    void build(const vector<vector<T>>& a) {
        int h = (int)a.size();
        int w = h ? (int)a[0].size() : 0;
        s.assign(h + 1, vector<T>(w + 1, 0));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                s[i + 1][j + 1] = s[i + 1][j] + s[i][j + 1] - s[i][j] + a[i][j];
            }
        }
    }

    T sum(int u, int d, int l, int r) const {
        return s[d][r] - s[u][r] - s[d][l] + s[u][l];
    }
};
