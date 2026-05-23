#include <bits/stdc++.h>
using namespace std;

/*
LowLink

無向グラフの橋・関節点・二重辺連結成分を求める。
多重辺も edge id で扱える。計算量 O(N+M)。

用語:
- 橋: その辺を消すと連結成分が増える辺。
- 関節点: その頂点を消すと連結成分が増える頂点。
- 二重辺連結成分: 橋を使わずに行き来できる頂点集合。

考え方:
DFS順 ord[v] と、DFS木の子孫から後退辺で戻れる最小の ord を low[v] に入れる。
辺 v-to について ord[v] < low[to] なら、to 側から v 以前へ戻る道がないので橋。
頂点 v について ord[v] <= low[to] となる子 to があるなら、v は関節点候補。
根だけは子が2つ以上あると関節点。
*/

struct LowLink {
    int n;
    vector<vector<pair<int, int>>> g;
    vector<int> ord, low;
    vector<pair<int, int>> bridges;
    vector<int> bridge_ids;
    vector<int> articulation;
    int edge_count = 0;
    int timer = 0;

    explicit LowLink(int n) : n(n), g(n) {}

    int add_edge(int u, int v) {
        int id = edge_count++;
        g[u].push_back({v, id});
        g[v].push_back({u, id});
        return id;
    }

    void build() {
        ord.assign(n, -1);
        low.assign(n, -1);
        bridges.clear();
        bridge_ids.clear();
        articulation.clear();
        timer = 0;
        for (int v = 0; v < n; v++) {
            if (ord[v] == -1) dfs(v, -1);
        }
        sort(articulation.begin(), articulation.end());
    }

    vector<int> two_edge_connected_components() const {
        vector<bool> is_bridge(edge_count);
        for (int id : bridge_ids) is_bridge[id] = true;

        vector<int> comp(n, -1);
        int comp_count = 0;
        for (int s = 0; s < n; s++) {
            if (comp[s] != -1) continue;
            queue<int> q;
            comp[s] = comp_count;
            q.push(s);
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (auto [to, id] : g[v]) {
                    if (is_bridge[id] || comp[to] != -1) continue;
                    comp[to] = comp_count;
                    q.push(to);
                }
            }
            comp_count++;
        }
        return comp;
    }

   private:
    void dfs(int v, int parent_edge) {
        ord[v] = low[v] = timer++;
        int child_count = 0;
        bool is_articulation = false;

        for (auto [to, id] : g[v]) {
            if (id == parent_edge) continue;
            if (ord[to] == -1) {
                child_count++;
                dfs(to, id);
                low[v] = min(low[v], low[to]);
                if (parent_edge != -1 && ord[v] <= low[to]) is_articulation = true;
                if (ord[v] < low[to]) {
                    bridges.push_back({min(v, to), max(v, to)});
                    bridge_ids.push_back(id);
                }
            } else {
                low[v] = min(low[v], ord[to]);
            }
        }

        if (parent_edge == -1 && child_count >= 2) is_articulation = true;
        if (is_articulation) articulation.push_back(v);
    }
};

/*
使用例:
LowLink low(n);
low.add_edge(u, v);
low.build();
for (auto [u, v] : low.bridges) cout << u << " " << v << "\n";
auto comp = low.two_edge_connected_components();
*/
