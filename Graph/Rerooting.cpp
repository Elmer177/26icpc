#include <bits/stdc++.h>
using namespace std;

/*
全方位木DP / rerooting

全頂点を根にしたときの木DPを O(N) で求める。
merge: 子からの値を合成する
add_edge(dp, edge_id, from, to): from 側の DP を edge 経由で to への寄与に変換する
add_vertex(dp, v): v 自身を足して、その部分木/成分の DP にする

何をしているか:
1回目のDFSで「適当な根から見た子部分木のDP」subdp[v] を作る。
2回目のDFSで「親側から来るDP」も渡し、各頂点 v について隣接成分すべてを merge して ans[v] を作る。
子へ降りるときは、その子以外の寄与を prefix/suffix で O(1) に取り出す。

DP の決め方:
- ident は merge の単位元。足し算なら 0、最大なら -INF など。
- merge は順番に依存しない形にするのが安全。
- add_edge は「辺を1本またいだら値がどう変わるか」を書く。
- add_vertex は「最後に頂点 v 自身を足す」処理を書く。

例の距離和では、DP{sum,size} を持つ。
子側の全頂点への距離 sum は、辺を1本またぐと各頂点まで +1 されるので sum + size になる。
*/

template <class DP, class Merge, class AddEdge, class AddVertex>
struct Rerooting {
    struct Edge {
        int to, id;
    };

    int n;
    vector<vector<Edge>> g;
    DP ident;
    Merge merge;
    AddEdge add_edge_value;
    AddVertex add_vertex;
    vector<DP> subdp, ans;
    int edge_count = 0;

    Rerooting(int n, DP ident, Merge merge, AddEdge add_edge_value, AddVertex add_vertex)
        : n(n),
          g(n),
          ident(ident),
          merge(merge),
          add_edge_value(add_edge_value),
          add_vertex(add_vertex) {}

    int add_edge(int u, int v) {
        int id = edge_count++;
        g[u].push_back({v, id});
        g[v].push_back({u, id});
        return id;
    }

    vector<DP> build(int root = 0) {
        if (n == 0) return {};
        subdp.assign(n, ident);
        ans.assign(n, ident);
        dfs1(root, -1);
        dfs2(root, ident, -1);
        return ans;
    }

   private:
    DP dfs1(int v, int parent_edge) {
        DP acc = ident;
        for (const auto& e : g[v]) {
            if (e.id == parent_edge) continue;
            DP child = dfs1(e.to, e.id);
            acc = merge(acc, add_edge_value(child, e.id, e.to, v));
        }
        return subdp[v] = add_vertex(acc, v);
    }

    void dfs2(int v, const DP& from_parent, int parent_edge) {
        int m = (int)g[v].size();
        vector<DP> val(m);
        for (int i = 0; i < m; i++) {
            const auto& e = g[v][i];
            if (e.id == parent_edge) {
                val[i] = add_edge_value(from_parent, e.id, e.to, v);
            } else {
                val[i] = add_edge_value(subdp[e.to], e.id, e.to, v);
            }
        }

        vector<DP> pref(m + 1, ident), suff(m + 1, ident);
        for (int i = 0; i < m; i++) pref[i + 1] = merge(pref[i], val[i]);
        for (int i = m - 1; i >= 0; i--) suff[i] = merge(val[i], suff[i + 1]);

        ans[v] = add_vertex(pref[m], v);

        for (int i = 0; i < m; i++) {
            const auto& e = g[v][i];
            if (e.id == parent_edge) continue;
            DP without_child = merge(pref[i], suff[i + 1]);
            DP next_parent = add_vertex(without_child, v);
            dfs2(e.to, next_parent, e.id);
        }
    }
};

/*
使用例: 各頂点から全頂点への距離和
struct DP { long long sum, size; };
auto merge = [](DP a, DP b) { return DP{a.sum + b.sum, a.size + b.size}; };
auto add_edge = [](DP a, int, int, int) { return DP{a.sum + a.size, a.size}; };
auto add_vertex = [](DP a, int) { return DP{a.sum, a.size + 1}; };
Rerooting<DP, decltype(merge), decltype(add_edge), decltype(add_vertex)>
    rr(n, DP{0, 0}, merge, add_edge, add_vertex);
rr.add_edge(u, v);
auto ans = rr.build();
*/
