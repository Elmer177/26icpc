#include <bits/stdc++.h>
using namespace std;

/*
最小費用流

各辺に容量とコストがある有向グラフで、指定した量を最小コストで流す。
割当問題、最小コストマッチング、輸送問題などで使う。

負辺も初回Bellman-Fordで扱えるが、負閉路がある場合は未定義。
*/

template <class Cap, class Cost>
struct MinCostFlow {
    struct edge {
        int from, to;
        Cap cap, flow;
        Cost cost;
    };

    MinCostFlow() : _n(0) {}
    explicit MinCostFlow(int n) : _n(n), g(n) {}

    int add_edge(int from, int to, Cap cap, Cost cost) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(0 <= cap);
        int m = (int)pos.size();
        int from_id = (int)g[from].size();
        int to_id = (int)g[to].size();
        if (from == to) to_id++;
        pos.push_back({from, from_id});
        g[from].push_back(_edge{to, to_id, cap, cost});
        g[to].push_back(_edge{from, from_id, 0, -cost});
        return m;
    }

    edge get_edge(int i) const {
        int m = (int)pos.size();
        assert(0 <= i && i < m);
        auto [from, id] = pos[i];
        const _edge& e = g[from][id];
        const _edge& re = g[e.to][e.rev];
        return edge{from, e.to, e.cap + re.cap, re.cap, e.cost};
    }

    vector<edge> edges() const {
        int m = (int)pos.size();
        vector<edge> result(m);
        for (int i = 0; i < m; i++) result[i] = get_edge(i);
        return result;
    }

    pair<Cap, Cost> flow(int s, int t) {
        return flow(s, t, numeric_limits<Cap>::max());
    }

    pair<Cap, Cost> flow(int s, int t, Cap flow_limit) {
        auto result = slope(s, t, flow_limit);
        return result.back();
    }

    vector<pair<Cap, Cost>> slope(int s, int t) {
        return slope(s, t, numeric_limits<Cap>::max());
    }

    vector<pair<Cap, Cost>> slope(int s, int t, Cap flow_limit) {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);

        const Cost INF_COST = numeric_limits<Cost>::max() / 4;
        vector<Cost> dual(_n, 0), dist(_n);
        vector<int> pv(_n), pe(_n);

        auto init_dual = [&]() {
            fill(dual.begin(), dual.end(), INF_COST);
            dual[s] = 0;
            for (int iter = 0; iter < _n - 1; iter++) {
                bool updated = false;
                for (int v = 0; v < _n; v++) {
                    if (dual[v] == INF_COST) continue;
                    for (const _edge& e : g[v]) {
                        if (e.cap == 0) continue;
                        if (dual[e.to] > dual[v] + e.cost) {
                            dual[e.to] = dual[v] + e.cost;
                            updated = true;
                        }
                    }
                }
                if (!updated) break;
            }
            for (int v = 0; v < _n; v++) {
                if (dual[v] == INF_COST) dual[v] = 0;
            }
        };

        auto shortest_path = [&]() -> bool {
            fill(dist.begin(), dist.end(), INF_COST);
            fill(pv.begin(), pv.end(), -1);
            fill(pe.begin(), pe.end(), -1);
            using P = pair<Cost, int>;
            priority_queue<P, vector<P>, greater<P>> pq;
            dist[s] = 0;
            pq.push({0, s});
            while (!pq.empty()) {
                auto [d, v] = pq.top();
                pq.pop();
                if (dist[v] != d) continue;
                for (int i = 0; i < (int)g[v].size(); i++) {
                    const _edge& e = g[v][i];
                    if (e.cap == 0) continue;
                    Cost nd = d + e.cost + dual[v] - dual[e.to];
                    if (dist[e.to] <= nd) continue;
                    dist[e.to] = nd;
                    pv[e.to] = v;
                    pe[e.to] = i;
                    pq.push({nd, e.to});
                }
            }
            if (dist[t] == INF_COST) return false;
            for (int v = 0; v < _n; v++) {
                if (dist[v] != INF_COST) dual[v] += dist[v];
            }
            return true;
        };

        init_dual();

        Cap flow = 0;
        Cost cost = 0;
        Cost prev_cost_per_flow = 0;
        bool has_prev = false;
        vector<pair<Cap, Cost>> result;
        result.push_back({flow, cost});

        while (flow < flow_limit) {
            if (!shortest_path()) break;
            Cap c = flow_limit - flow;
            for (int v = t; v != s; v = pv[v]) {
                c = min(c, g[pv[v]][pe[v]].cap);
            }
            for (int v = t; v != s; v = pv[v]) {
                _edge& e = g[pv[v]][pe[v]];
                e.cap -= c;
                g[v][e.rev].cap += c;
            }
            Cost d = dual[t] - dual[s];
            flow += c;
            cost += c * d;
            if (has_prev && prev_cost_per_flow == d) result.pop_back();
            result.push_back({flow, cost});
            prev_cost_per_flow = d;
            has_prev = true;
        }
        return result;
    }

   private:
    struct _edge {
        int to, rev;
        Cap cap;
        Cost cost;
    };

    int _n;
    vector<pair<int, int>> pos;
    vector<vector<_edge>> g;
};

/*
使用例:
MinCostFlow<long long, long long> g(n);
g.add_edge(u, v, cap, cost);
auto [flow, cost] = g.flow(s, t, need);
*/
