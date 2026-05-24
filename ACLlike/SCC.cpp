#include <bits/stdc++.h>
using namespace std;

/*
強連結成分分解

有向グラフを「互いに行き来できる頂点集合」に分ける。
縮約するとDAGになるので、依存関係や到達可能性の整理に使える。

- add_edge(from, to): 有向辺 from -> to を追加する
- scc(): 強連結成分の配列を返す。成分の並びはトポロジカル順。
*/

struct SCCGraph {
    int n;
    vector<vector<int>> g, rg;

    SCCGraph() : n(0) {}
    explicit SCCGraph(int n_) : n(n_), g(n_), rg(n_) {}

    void add_edge(int from, int to) {
        assert(0 <= from && from < n);
        assert(0 <= to && to < n);
        g[from].push_back(to);
        rg[to].push_back(from);
    }

    vector<vector<int>> scc() const {
        vector<int> order, used(n, 0), comp(n, -1);
        order.reserve(n);

        auto dfs1 = [&](auto self, int v) -> void {
            used[v] = 1;
            for (int to : g[v]) {
                if (!used[to]) self(self, to);
            }
            order.push_back(v);
        };
        for (int v = 0; v < n; v++) {
            if (!used[v]) dfs1(dfs1, v);
        }

        vector<vector<int>> groups;
        auto dfs2 = [&](auto self, int v, int id) -> void {
            comp[v] = id;
            groups.back().push_back(v);
            for (int to : rg[v]) {
                if (comp[to] == -1) self(self, to, id);
            }
        };
        reverse(order.begin(), order.end());
        for (int v : order) {
            if (comp[v] != -1) continue;
            groups.push_back({});
            dfs2(dfs2, v, (int)groups.size() - 1);
        }
        return groups;
    }
};

/*
使用例:
SCCGraph g(n);
g.add_edge(u, v);
auto groups = g.scc();
*/
