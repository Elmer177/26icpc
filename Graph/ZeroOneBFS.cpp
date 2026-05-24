#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int ZERO_ONE_BFS_INF = 1e9;

/*
0-1 BFS

辺重みが 0 または 1 のグラフの単一始点最短路。
Dijkstraより軽く、dequeで処理できる。

g[u] = {{v, cost}, ...}, cost は 0 または 1。
未到達は ZERO_ONE_BFS_INF。計算量 O(N+M)。
*/
vector<int> zero_one_bfs(const vector<vector<pair<int, int>>>& g, int s) {
    int n = (int)g.size();
    vector<int> dist(n, ZERO_ONE_BFS_INF);
    deque<int> dq;
    dist[s] = 0;
    dq.push_front(s);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (auto [v, cost] : g[u]) {
            if (dist[v] <= dist[u] + cost) continue;
            dist[v] = dist[u] + cost;
            if (cost == 0) dq.push_front(v);
            else dq.push_back(v);
        }
    }
    return dist;
}

/*
使用例:
vector<vector<pair<int,int>>> g(n);
g[u].push_back({v, 0});
g[u].push_back({w, 1});
auto dist = zero_one_bfs(g, 0);
*/
