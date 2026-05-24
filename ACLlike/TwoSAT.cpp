#include <bits/stdc++.h>
using namespace std;

/*
2-SAT

真偽値の変数について、(条件A または 条件B) という制約をたくさん満たせるか判定する。
選ぶ/選ばない、表/裏、左右どちらか、のような二択制約で使う。

- add_clause(i, f, j, g): (x_i == f) OR (x_j == g) を追加する
- satisfiable(): すべての制約を満たせるなら true
- answer(): satisfiable() が true のときの一例を返す
*/

struct TwoSAT {
    int _n;
    vector<vector<int>> g, rg;
    vector<bool> _answer;

    TwoSAT() : _n(0) {}
    explicit TwoSAT(int n) : _n(n), g(2 * n), rg(2 * n), _answer(n) {}

    int id(int i, bool f) const {
        return 2 * i + (f ? 1 : 0);
    }

    void add_implication(int a, int b) {
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    void add_clause(int i, bool f, int j, bool g_value) {
        assert(0 <= i && i < _n);
        assert(0 <= j && j < _n);
        add_implication(id(i, !f), id(j, g_value));
        add_implication(id(j, !g_value), id(i, f));
    }

    bool satisfiable() {
        int n2 = 2 * _n;
        vector<int> order, used(n2, 0), comp(n2, -1);
        order.reserve(n2);

        auto dfs1 = [&](auto self, int v) -> void {
            used[v] = 1;
            for (int to : g[v]) {
                if (!used[to]) self(self, to);
            }
            order.push_back(v);
        };
        for (int v = 0; v < n2; v++) {
            if (!used[v]) dfs1(dfs1, v);
        }

        auto dfs2 = [&](auto self, int v, int c) -> void {
            comp[v] = c;
            for (int to : rg[v]) {
                if (comp[to] == -1) self(self, to, c);
            }
        };
        reverse(order.begin(), order.end());
        int cid = 0;
        for (int v : order) {
            if (comp[v] == -1) dfs2(dfs2, v, cid++);
        }

        for (int i = 0; i < _n; i++) {
            if (comp[id(i, false)] == comp[id(i, true)]) return false;
            _answer[i] = comp[id(i, false)] < comp[id(i, true)];
        }
        return true;
    }

    vector<bool> answer() const {
        return _answer;
    }
};

/*
使用例:
TwoSAT ts(n);
ts.add_clause(i, true, j, false);
if (ts.satisfiable()) {
    auto ans = ts.answer();
}
*/
