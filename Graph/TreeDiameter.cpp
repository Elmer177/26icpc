#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
木の直径

木上で最も遠い2頂点とその距離を求める。
重みなし木なら cost=1 にする。
計算量 O(N)。

g[u] = {{v, cost}, ...}
*/
struct TreeDiameterResult {
    int u, v;
    ll dist;
};

pair<int, ll> farthest_vertex(const vector<vector<pair<int, ll>>>& g, int s) {
    int n = (int)g.size();
    vector<ll> dist(n, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, cost] : g[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + cost;
            q.push(v);
        }
    }

    int best = s;
    for (int i = 0; i < n; i++) {
        if (dist[best] < dist[i]) best = i;
    }
    return {best, dist[best]};
}

TreeDiameterResult tree_diameter(const vector<vector<pair<int, ll>>>& g) {
    auto [a, _] = farthest_vertex(g, 0);
    auto [b, d] = farthest_vertex(g, a);
    return {a, b, d};
}

/*
使用例:
vector<vector<pair<int,ll>>> g(n);
g[u].push_back({v, 1});
g[v].push_back({u, 1});
auto res = tree_diameter(g);
cout << res.dist << "\n";
*/
