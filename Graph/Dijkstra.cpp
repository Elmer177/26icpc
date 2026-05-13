#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll DIJKSTRA_INF = 4e18;

/*
Dijkstra

辺重みがすべて 0 以上のグラフで使う単一始点最短路。
負辺がある場合は使えない。

g[u] = {{v, cost}, ...}
未到達は DIJKSTRA_INF。計算量 O((N+M) log N)。
*/
vector<ll> dijkstra(const vector<vector<pair<int, ll>>>& g, int s) {
    int n = (int)g.size();
    vector<ll> dist(n, DIJKSTRA_INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, cost] : g[u]) {
            if (dist[v] <= d + cost) continue;
            dist[v] = d + cost;
            pq.push({dist[v], v});
        }
    }
    return dist;
}

/*
使用例:
vector<vector<pair<int,ll>>> g(n);
g[u].push_back({v, w});
g[v].push_back({u, w}); // 無向グラフなら両方
auto dist = dijkstra(g, 0);
*/
