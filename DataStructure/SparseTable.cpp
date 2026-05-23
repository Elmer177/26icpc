#include <bits/stdc++.h>
using namespace std;

/*
Sparse Table

min/max/gcd など、結合的かつ同じ要素を二回使ってもよい演算で区間クエリ。
構築 O(N log N), クエリ O(1)。
query(l, r) は半開区間 [l, r)。

考え方:
table[k][i] に長さ 2^k の区間 [i, i+2^k) の答えを持つ。
クエリ [l,r) は長さ 2^k の区間2つで覆う:
  [l, l+2^k) と [r-2^k, r)
この2つは重なることがあるので、min/max/gcd のように同じ要素を二回使っても答えが変わらない演算向け。
sum など重ねると値が変わる演算には普通のセグ木を使う。
*/

template <class T, class F>
struct SparseTable {
    int n;
    vector<int> lg;
    vector<vector<T>> table;
    F op;

    SparseTable(const vector<T>& v, F op) : n((int)v.size()), op(op) {
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
        table.assign(lg[n] + 1, vector<T>(n));
        if (n == 0) return;
        table[0] = v;
        for (int k = 1; k < (int)table.size(); k++) {
            int len = 1 << k;
            for (int i = 0; i + len <= n; i++) {
                table[k][i] = op(table[k - 1][i], table[k - 1][i + (len >> 1)]);
            }
        }
    }

    T query(int l, int r) const {
        assert(0 <= l && l < r && r <= n);
        int k = lg[r - l];
        return op(table[k][l], table[k][r - (1 << k)]);
    }
};

/*
使用例:
vector<long long> a(n);
auto op = [](long long x, long long y) { return min(x, y); };
SparseTable<long long, decltype(op)> st(a, op);
cout << st.query(l, r) << "\n"; // min a[l..r)
*/
