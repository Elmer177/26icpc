#include <bits/stdc++.h>
using namespace std;

/*
Hopcroft-Karp

二部グラフの最大マッチング。
左側 0..n_left-1, 右側 0..n_right-1。
計算量 O(E sqrt(V))。

最大マッチング:
辺を選んで、各頂点が高々1本の選んだ辺にしか使われないようにしたときの最大本数。
「人と仕事の割当」「行と列の対応」「グリッドで隣り合うマスをペアにする」などで使う。

考え方:
今のマッチングに対して、未マッチの左頂点から始まり未マッチの右頂点で終わる交互路を探す。
交互路に沿って選ぶ/選ばないを反転するとマッチングが1増える。
Hopcroft-Karp は BFS で最短の交互路の層を作り、DFS で同じ長さの交互路をまとめて増やす。

minimum_vertex_cover() は max_matching() を呼んだ後に使う。
二部グラフでは「最大マッチングサイズ = 最小点カバーサイズ」。
*/

struct HopcroftKarp {
    int n_left, n_right;
    vector<vector<int>> g;
    vector<int> match_left, match_right, dist;

    HopcroftKarp(int n_left, int n_right)
        : n_left(n_left), n_right(n_right), g(n_left), match_left(n_left, -1), match_right(n_right, -1), dist(n_left) {}

    void add_edge(int left, int right) {
        assert(0 <= left && left < n_left);
        assert(0 <= right && right < n_right);
        g[left].push_back(right);
    }

    int max_matching() {
        int matching = 0;
        while (bfs()) {
            for (int v = 0; v < n_left; v++) {
                if (match_left[v] == -1 && dfs(v)) matching++;
            }
        }
        return matching;
    }

    vector<pair<int, int>> pairs() const {
        vector<pair<int, int>> res;
        for (int l = 0; l < n_left; l++) {
            if (match_left[l] != -1) res.push_back({l, match_left[l]});
        }
        return res;
    }

    pair<vector<int>, vector<int>> minimum_vertex_cover() const {
        vector<bool> vis_left(n_left), vis_right(n_right);
        queue<int> q;
        for (int l = 0; l < n_left; l++) {
            if (match_left[l] == -1) {
                vis_left[l] = true;
                q.push(l);
            }
        }

        while (!q.empty()) {
            int l = q.front();
            q.pop();
            for (int r : g[l]) {
                if (match_left[l] == r || vis_right[r]) continue;
                vis_right[r] = true;
                int nl = match_right[r];
                if (nl != -1 && !vis_left[nl]) {
                    vis_left[nl] = true;
                    q.push(nl);
                }
            }
        }

        vector<int> left_cover, right_cover;
        for (int l = 0; l < n_left; l++) {
            if (!vis_left[l]) left_cover.push_back(l);
        }
        for (int r = 0; r < n_right; r++) {
            if (vis_right[r]) right_cover.push_back(r);
        }
        return {left_cover, right_cover};
    }

   private:
    bool bfs() {
        queue<int> q;
        fill(dist.begin(), dist.end(), -1);
        for (int v = 0; v < n_left; v++) {
            if (match_left[v] == -1) {
                dist[v] = 0;
                q.push(v);
            }
        }

        bool found = false;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int r : g[v]) {
                int to = match_right[r];
                if (to == -1) {
                    found = true;
                } else if (dist[to] == -1) {
                    dist[to] = dist[v] + 1;
                    q.push(to);
                }
            }
        }
        return found;
    }

    bool dfs(int v) {
        for (int r : g[v]) {
            int to = match_right[r];
            if (to == -1 || (dist[to] == dist[v] + 1 && dfs(to))) {
                match_left[v] = r;
                match_right[r] = v;
                return true;
            }
        }
        dist[v] = -1;
        return false;
    }
};

/*
使用例:
HopcroftKarp hk(n_left, n_right);
hk.add_edge(l, r);
cout << hk.max_matching() << "\n";
for (auto [l, r] : hk.pairs()) cout << l << " " << r << "\n";
*/
