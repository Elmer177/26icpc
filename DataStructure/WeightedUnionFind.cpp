#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
重み付きUnion-Find

各頂点にポテンシャル weight[x] があると考え、
「weight[y] - weight[x] = w」という制約を管理する。

差分制約、矛盾判定、座標の相対位置管理で使う。
ほぼ amortized O(alpha(N))。
*/
struct WeightedUnionFind {
    vector<int> parent, sz;
    vector<ll> diff_weight; // diff_weight[x] = weight[x] - weight[parent[x]]

    WeightedUnionFind(int n) : parent(n), sz(n, 1), diff_weight(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int root(int x) {
        if (parent[x] == x) return x;
        int r = root(parent[x]);
        diff_weight[x] += diff_weight[parent[x]];
        return parent[x] = r;
    }

    ll weight(int x) {
        root(x);
        return diff_weight[x];
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    }

    // 矛盾なく追加できたら true
    bool unite(int x, int y, ll w) {
        w += weight(x);
        w -= weight(y);
        x = root(x);
        y = root(y);
        if (x == y) return w == 0;
        if (sz[x] < sz[y]) {
            swap(x, y);
            w = -w;
        }
        parent[y] = x;
        sz[x] += sz[y];
        diff_weight[y] = w;
        return true;
    }

    // same(x, y) が true のときだけ使う
    ll diff(int x, int y) {
        return weight(y) - weight(x);
    }
};

/*
使用例:
WeightedUnionFind uf(3);
uf.unite(0, 1, 5); // weight[1] - weight[0] = 5
uf.unite(1, 2, 7); // weight[2] - weight[1] = 7
cout << uf.diff(0, 2) << "\n"; // 12

if (!uf.unite(0, 2, 11)) {
    // 既存制約と矛盾
}
*/
