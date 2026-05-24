#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
最小全域木 MST

Kruskal: 辺リスト + Union-Find。計算量 O(M log M)。
Prim: 隣接リスト。計算量 O(M log N)。
*/

struct MSTDSU {
    vector<int> parent_or_size;

    MSTDSU() {}
    explicit MSTDSU(int n) : parent_or_size(n, -1) {}

    int leader(int a) {
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    bool merge(int a, int b) {
        int x = leader(a), y = leader(b);
        if (x == y) return false;
        if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return true;
    }
};

struct MSTEdge {
    int u, v, id;
    ll cost;

    MSTEdge() {}
    MSTEdge(int u, int v, ll cost, int id = -1) : u(u), v(v), id(id), cost(cost) {}
};

struct MSTResult {
    ll cost;
    vector<int> edge_ids;
    bool connected;
};

MSTResult kruskal(int n, vector<MSTEdge> edges) {
    for (int i = 0; i < (int)edges.size(); i++) {
        if (edges[i].id == -1) edges[i].id = i;
    }
    sort(edges.begin(), edges.end(), [](const MSTEdge& a, const MSTEdge& b) {
        return a.cost < b.cost;
    });

    MSTDSU dsu(n);
    ll cost = 0;
    vector<int> used;
    for (const auto& e : edges) {
        if (!dsu.merge(e.u, e.v)) continue;
        cost += e.cost;
        used.push_back(e.id);
    }
    return {cost, used, (int)used.size() == n - 1};
}

MSTResult prim_mst(const vector<vector<pair<int, ll>>>& g, int start = 0) {
    int n = (int)g.size();
    if (n == 0) return {0, {}, true};

    vector<bool> used(n);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({0, start});

    ll cost = 0;
    int cnt = 0;
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (used[v]) continue;
        used[v] = true;
        cost += d;
        cnt++;
        for (auto [to, w] : g[v]) {
            if (!used[to]) pq.push({w, to});
        }
    }
    return {cost, {}, cnt == n};
}

/*
使用例:
vector<MSTEdge> edges;
edges.push_back({u, v, w});
auto res = kruskal(n, edges);
if (!res.connected) cout << "disconnected\n";
else cout << res.cost << "\n";
*/
