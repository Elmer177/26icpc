#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
トポロジカルソート

DAG(有向非巡回グラフ)で、すべての辺 u -> v について u が v より前に来る順序を作る。
DPを依存順に回したいときに使う。
閉路がある場合は空配列を返す。計算量 O(N+M)。
*/
vector<int> topological_sort(const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; u++) {
        for (int v : g[u]) indeg[v]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) q.push(i);
    }

    vector<int> order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : g[u]) {
            indeg[v]--;
            if (indeg[v] == 0) q.push(v);
        }
    }

    if ((int)order.size() != n) return {};
    return order;
}

/*
使用例:
vector<vector<int>> g(n);
g[u].push_back(v); // 有向辺 u -> v
auto order = topological_sort(g);
if (order.empty()) {
    // 閉路あり
}
*/
