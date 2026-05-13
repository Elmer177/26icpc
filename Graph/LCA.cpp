#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
LCA: Lowest Common Ancestor

木上の2頂点の最近共通祖先を求める。
木は0-indexed。辺を追加して build(root) 後に lca/dist を使う。

前計算 O(N log N), クエリ O(log N)。
*/
struct LCA {
    int n, lg;
    vector<int> depth;
    vector<vector<int>> parent;
    vector<vector<int>> g;

    LCA(int n_) : n(n_), lg(1), depth(n_), g(n_) {
        while ((1 << lg) <= n) lg++;
        parent.assign(lg, vector<int>(n, -1));
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void build(int root = 0) {
        queue<int> q;
        depth[root] = 0;
        parent[0][root] = -1;
        q.push(root);
        vector<int> seen(n, 0);
        seen[root] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (seen[v]) continue;
                seen[v] = 1;
                depth[v] = depth[u] + 1;
                parent[0][v] = u;
                q.push(v);
            }
        }

        for (int k = 0; k + 1 < lg; k++) {
            for (int v = 0; v < n; v++) {
                if (parent[k][v] == -1) parent[k + 1][v] = -1;
                else parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }
    }

    int climb(int v, int d) const {
        for (int k = 0; k < lg; k++) {
            if (d >> k & 1) v = parent[k][v];
        }
        return v;
    }

    int lca(int a, int b) const {
        if (depth[a] < depth[b]) swap(a, b);
        a = climb(a, depth[a] - depth[b]);
        if (a == b) return a;
        for (int k = lg - 1; k >= 0; k--) {
            if (parent[k][a] != parent[k][b]) {
                a = parent[k][a];
                b = parent[k][b];
            }
        }
        return parent[0][a];
    }

    int dist(int a, int b) const {
        int c = lca(a, b);
        return depth[a] + depth[b] - 2 * depth[c];
    }
};

/*
使用例:
LCA lca(n);
lca.add_edge(u, v);
lca.build(0);

int p = lca.lca(a, b);
int d = lca.dist(a, b);
*/
