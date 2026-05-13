#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
BFS

重みなしグラフの単一始点最短距離。
g[u] に u から行ける頂点を入れる。0-indexed。
未到達は -1。計算量 O(N+M)。
*/
vector<int> bfs_dist(const vector<vector<int>>& g, int s) {
    int n = (int)g.size();
    vector<int> dist(n, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    return dist;
}

/*
使用例:
vector<vector<int>> g(n);
g[u].push_back(v);
g[v].push_back(u);
auto dist = bfs_dist(g, 0);
*/
