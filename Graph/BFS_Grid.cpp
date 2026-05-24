#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const vector<int> DX4 = {1, 0, -1, 0};
const vector<int> DY4 = {0, 1, 0, -1};
const vector<int> DX8 = {1, 1, 0, -1, -1, -1, 0, 1};
const vector<int> DY8 = {0, 1, 1, 1, 0, -1, -1, -1};

/*
グリッドBFS

grid[x][y] != wall のマスを通れるとして、(sx, sy) からの最短距離を返す。
未到達は -1。計算量 O(HW)。

座標は (行, 列) = (x, y)。
問題文が (r, c) で1-indexedなら、入力後に --r, --c する。
*/
vector<vector<int>> grid_bfs_dist(const vector<string>& grid, int sx, int sy, char wall = '#') {
    int h = (int)grid.size();
    int w = h ? (int)grid[0].size() : 0;
    vector<vector<int>> dist(h, vector<int>(w, -1));
    queue<pair<int, int>> q;
    dist[sx][sy] = 0;
    q.push({sx, sy});

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int dir = 0; dir < 4; dir++) {
            int nx = x + DX4[dir];
            int ny = y + DY4[dir];
            if (nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
            if (grid[nx][ny] == wall) continue;
            if (dist[nx][ny] != -1) continue;
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }
    return dist;
}

/*
使用例:
auto dist = grid_bfs_dist(S, sh, sw);
cout << dist[gh][gw] << "\n";

8近傍を使いたいときは、ループ内の DX4/DY4 を DX8/DY8 に変える。
*/
