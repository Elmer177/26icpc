#include <bits/stdc++.h>
using namespace std;

/*
Heavy-Light Decomposition

木上パスを O(log N) 個の連続区間に分解する。
セグ木/Fenwick と組み合わせてパスクエリ・部分木クエリに使う。
pos[v] が HLD 順、subtree_range(v) が部分木の半開区間。

考え方:
各頂点で一番大きい子部分木へ向かう辺を heavy edge として、heavy edge をなるべく同じ列に並べる。
すると根から任意の頂点へ行く途中で列を乗り換える回数が O(log N) になる。
列の中では pos が連続なので、木上パスをいくつかの配列区間に分けられる。

よく使う場面:
- 頂点値のパス和/最大値: for_each_vertex_path(a,b, ...) で区間クエリを合成。
- 辺値のパス和/最大値: 辺の値を「深い側の頂点 pos」に置き、for_each_edge_path を使う。
- 部分木クエリ: subtree_range(v) がそのまま連続区間。
*/

struct HeavyLightDecomposition {
    int n;
    vector<vector<int>> g;
    vector<int> parent, depth, heavy, head, pos, inv, subtree;
    int timer = 0;

    explicit HeavyLightDecomposition(int n) : n(n), g(n) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void build(int root = 0) {
        parent.assign(n, -1);
        depth.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, -1);
        pos.assign(n, -1);
        inv.assign(n, -1);
        subtree.assign(n, 0);
        timer = 0;
        dfs_size(root, -1);
        dfs_hld(root, root);
    }

    int lca(int a, int b) const {
        while (head[a] != head[b]) {
            if (depth[head[a]] > depth[head[b]]) a = parent[head[a]];
            else b = parent[head[b]];
        }
        return depth[a] < depth[b] ? a : b;
    }

    int dist(int a, int b) const {
        int c = lca(a, b);
        return depth[a] + depth[b] - 2 * depth[c];
    }

    pair<int, int> subtree_range(int v) const {
        return {pos[v], pos[v] + subtree[v]};
    }

    template <class F>
    void for_each_vertex_path(int a, int b, F f) const {
        while (head[a] != head[b]) {
            if (depth[head[a]] < depth[head[b]]) swap(a, b);
            f(pos[head[a]], pos[a] + 1);
            a = parent[head[a]];
        }
        if (depth[a] > depth[b]) swap(a, b);
        f(pos[a], pos[b] + 1);
    }

    template <class F>
    void for_each_edge_path(int a, int b, F f) const {
        while (head[a] != head[b]) {
            if (depth[head[a]] < depth[head[b]]) swap(a, b);
            f(pos[head[a]], pos[a] + 1);
            a = parent[head[a]];
        }
        if (depth[a] > depth[b]) swap(a, b);
        f(pos[a] + 1, pos[b] + 1);
    }

   private:
    int dfs_size(int v, int p) {
        parent[v] = p;
        subtree[v] = 1;
        int best_size = 0;
        for (int to : g[v]) {
            if (to == p) continue;
            depth[to] = depth[v] + 1;
            int sz = dfs_size(to, v);
            subtree[v] += sz;
            if (sz > best_size) {
                best_size = sz;
                heavy[v] = to;
            }
        }
        return subtree[v];
    }

    void dfs_hld(int v, int h) {
        head[v] = h;
        pos[v] = timer;
        inv[timer] = v;
        timer++;
        if (heavy[v] != -1) dfs_hld(heavy[v], h);
        for (int to : g[v]) {
            if (to == parent[v] || to == heavy[v]) continue;
            dfs_hld(to, to);
        }
    }
};

/*
使用例:
HeavyLightDecomposition hld(n);
hld.add_edge(u, v);
hld.build(0);
hld.for_each_vertex_path(a, b, [&](int l, int r) {
    // seg.prod(l, r) など
});
auto [l, r] = hld.subtree_range(v); // v の部分木
*/
