#include <bits/stdc++.h>
using namespace std;

/*
最大流

各辺に容量がある有向グラフで、始点から終点へ流せる最大量を求める。
Dinic法。二部マッチングにも使える。
*/

template <class Cap>
struct MaxFlow {
    struct edge {
        int from, to;
        Cap cap, flow;
    };

    MaxFlow() : _n(0) {}
    explicit MaxFlow(int n) : _n(n), g(n) {}

    int add_edge(int from, int to, Cap cap) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(0 <= cap);
        int m = (int)pos.size();
        int from_id = (int)g[from].size();
        int to_id = (int)g[to].size();
        if (from == to) to_id++;
        pos.push_back({from, from_id});
        g[from].push_back(_edge{to, to_id, cap});
        g[to].push_back(_edge{from, from_id, 0});
        return m;
    }

    edge get_edge(int i) const {
        int m = (int)pos.size();
        assert(0 <= i && i < m);
        auto [from, id] = pos[i];
        const _edge& e = g[from][id];
        const _edge& re = g[e.to][e.rev];
        return edge{from, e.to, e.cap + re.cap, re.cap};
    }

    vector<edge> edges() const {
        int m = (int)pos.size();
        vector<edge> result(m);
        for (int i = 0; i < m; i++) result[i] = get_edge(i);
        return result;
    }

    void change_edge(int i, Cap new_cap, Cap new_flow) {
        int m = (int)pos.size();
        assert(0 <= i && i < m);
        assert(0 <= new_flow && new_flow <= new_cap);
        auto [from, id] = pos[i];
        _edge& e = g[from][id];
        _edge& re = g[e.to][e.rev];
        e.cap = new_cap - new_flow;
        re.cap = new_flow;
    }

    Cap flow(int s, int t) {
        return flow(s, t, numeric_limits<Cap>::max());
    }

    Cap flow(int s, int t, Cap flow_limit) {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);
        Cap flow = 0;
        vector<int> level(_n), iter(_n);

        auto bfs = [&]() {
            fill(level.begin(), level.end(), -1);
            queue<int> que;
            level[s] = 0;
            que.push(s);
            while (!que.empty()) {
                int v = que.front();
                que.pop();
                for (const _edge& e : g[v]) {
                    if (e.cap == 0 || level[e.to] >= 0) continue;
                    level[e.to] = level[v] + 1;
                    if (e.to == t) return;
                    que.push(e.to);
                }
            }
        };

        auto dfs = [&](auto self, int v, Cap up) -> Cap {
            if (v == t) return up;
            Cap res = 0;
            for (int& i = iter[v]; i < (int)g[v].size(); i++) {
                _edge& e = g[v][i];
                if (e.cap == 0 || level[v] >= level[e.to]) continue;
                Cap d = self(self, e.to, min(up - res, e.cap));
                if (d == 0) continue;
                e.cap -= d;
                g[e.to][e.rev].cap += d;
                res += d;
                if (res == up) return res;
            }
            return res;
        };

        while (flow < flow_limit) {
            bfs();
            if (level[t] == -1) break;
            fill(iter.begin(), iter.end(), 0);
            while (flow < flow_limit) {
                Cap f = dfs(dfs, s, flow_limit - flow);
                if (f == 0) break;
                flow += f;
            }
        }
        return flow;
    }

    vector<bool> min_cut(int s) const {
        assert(0 <= s && s < _n);
        vector<bool> visited(_n);
        queue<int> que;
        visited[s] = true;
        que.push(s);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (const _edge& e : g[v]) {
                if (e.cap == 0 || visited[e.to]) continue;
                visited[e.to] = true;
                que.push(e.to);
            }
        }
        return visited;
    }

   private:
    struct _edge {
        int to, rev;
        Cap cap;
    };

    int _n;
    vector<pair<int, int>> pos;
    vector<vector<_edge>> g;
};

/*
使用例:
MaxFlow<long long> g(n);
g.add_edge(s, v, cap);
cout << g.flow(s, t) << "\n";
*/
