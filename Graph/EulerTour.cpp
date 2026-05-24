#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
木のオイラーツアー

根付き木として見たとき、頂点vの部分木を連続区間に変換する。
頂点vの部分木は order[tin[v] ... tout[v]-1]。
部分木クエリを Fenwick / Segment Tree に乗せるときに使う。

build(root): O(N)
*/
struct EulerTour {
    int n;
    vector<vector<int>> g;
    vector<int> tin, tout, parent, depth, order;

    EulerTour(int n_) : n(n_), g(n_), tin(n_), tout(n_), parent(n_, -1), depth(n_) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void build(int root = 0) {
        order.clear();
        dfs(root, -1, 0);
    }

    void dfs(int u, int p, int d) {
        parent[u] = p;
        depth[u] = d;
        tin[u] = (int)order.size();
        order.push_back(u);
        for (int v : g[u]) {
            if (v == p) continue;
            dfs(v, u, d + 1);
        }
        tout[u] = (int)order.size();
    }
};

/*
使用例:
EulerTour et(n);
et.add_edge(u, v);
et.build(0);

// 頂点vの部分木に対応する区間
int l = et.tin[v];
int r = et.tout[v];
*/
