#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
Bellman-Ford

負辺ありの単一始点最短路。
始点から到達でき、負閉路の影響を受ける頂点は negative[v] = true。
計算量 O(NM)。

使いどころ:
- Dijkstra は負辺があると使えないので、負辺がある単一始点最短路で使う。
- N 回目にも更新される頂点は「負閉路の影響で距離を無限に小さくできる」。
- negative[v] は、負閉路そのものだけでなく、そこから到達できる頂点にも伝播している。

注意:
has_negative_cycle は「始点 s から到達できる負閉路があるか」。
グラフ全体の負閉路を見たいなら、全頂点から辺を張るダミー始点を足す。
*/

const ll BELLMAN_FORD_INF = 4000000000000000000LL;

struct BellmanFordEdge {
    int from, to;
    ll cost;
};

struct BellmanFordResult {
    vector<ll> dist;
    vector<bool> negative;
    bool has_negative_cycle;
};

ll clamp_bellman_dist(__int128 x) {
    if (x > BELLMAN_FORD_INF) return BELLMAN_FORD_INF;
    if (x < -(__int128)BELLMAN_FORD_INF) return -BELLMAN_FORD_INF;
    return (ll)x;
}

BellmanFordResult bellman_ford(int n, const vector<BellmanFordEdge>& edges, int s) {
    vector<ll> dist(n, BELLMAN_FORD_INF);
    vector<bool> negative(n);
    dist[s] = 0;

    for (int i = 0; i < n; i++) {
        bool updated = false;
        for (const auto& e : edges) {
            if (dist[e.from] == BELLMAN_FORD_INF) continue;
            __int128 nd = (__int128)dist[e.from] + e.cost;
            if (nd < dist[e.to]) {
                dist[e.to] = clamp_bellman_dist(nd);
                updated = true;
                if (i == n - 1) negative[e.to] = true;
            }
        }
        if (!updated) break;
    }

    for (int i = 0; i < n; i++) {
        for (const auto& e : edges) {
            if (negative[e.from]) negative[e.to] = true;
        }
    }

    bool has_negative_cycle = false;
    for (bool x : negative) has_negative_cycle |= x;
    return {dist, negative, has_negative_cycle};
}

/*
使用例:
vector<BellmanFordEdge> edges;
edges.push_back({u, v, cost});
auto res = bellman_ford(n, edges, s);
if (res.negative[t]) cout << "-inf\n";
else if (res.dist[t] == BELLMAN_FORD_INF) cout << "unreachable\n";
else cout << res.dist[t] << "\n";
*/
