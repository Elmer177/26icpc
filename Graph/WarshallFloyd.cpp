#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll WARSHALL_FLOYD_INF = 4000000000000000000LL;

/*
Warshall-Floyd

全点対最短路。Nが小さいとき向け。
負辺があっても使えるが、負閉路があると最短距離は定義できない。

dist[i][i] = 0, 辺がないところは WARSHALL_FLOYD_INF にして渡す。
計算量 O(N^3)。
*/
void warshall_floyd(vector<vector<ll>>& dist) {
    int n = (int)dist.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dist[i][k] == WARSHALL_FLOYD_INF) continue;
            for (int j = 0; j < n; j++) {
                if (dist[k][j] == WARSHALL_FLOYD_INF) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

// 負閉路があるか
bool has_negative_cycle(const vector<vector<ll>>& dist) {
    int n = (int)dist.size();
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) return true;
    }
    return false;
}

/*
使用例:
vector dist(n, vector<ll>(n, WARSHALL_FLOYD_INF));
for (int i = 0; i < n; i++) dist[i][i] = 0;
dist[u][v] = min(dist[u][v], cost);
warshall_floyd(dist);
*/
