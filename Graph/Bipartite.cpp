#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
二部グラフ判定

隣接する頂点を必ず違う色に塗れるかを判定する。
連結でないグラフも全成分を見る。
color は -1: 未訪問, 0/1: 色。
計算量 O(N+M)。
*/
bool is_bipartite(const vector<vector<int>>& g, vector<int>& color) {
    int n = (int)g.size();
    color.assign(n, -1);
    for (int s = 0; s < n; s++) {
        if (color[s] != -1) continue;
        queue<int> q;
        color[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return false;
                }
            }
        }
    }
    return true;
}

/*
使用例:
vector<int> color;
if (is_bipartite(g, color)) {
    // color[i] が 0/1 のどちら側か
}
*/
