#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
DFS

到達可能性、連結成分、木DPの下準備などで使う。
再帰DFSは書きやすいが、長いパス状の木ではスタックオーバーフローに注意。
頂点数が大きいときは stack を使うか BFS にする。
*/

// 再帰DFSテンプレート。seen は n 要素で 0 初期化して渡す。
void dfs_recursive(const vector<vector<int>>& g, int s, vector<int>& seen) {
    seen[s] = 1;
    for (int v : g[s]) {
        if (seen[v]) continue;
        dfs_recursive(g, v, seen);
    }
}

// 連結成分番号
vector<int> connected_components(const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<int> comp(n, -1);
    int id = 0;
    for (int s = 0; s < n; s++) {
        if (comp[s] != -1) continue;
        stack<int> st;
        st.push(s);
        comp[s] = id;
        while (!st.empty()) {
            int u = st.top();
            st.pop();
            for (int v : g[u]) {
                if (comp[v] != -1) continue;
                comp[v] = id;
                st.push(v);
            }
        }
        id++;
    }
    return comp;
}

/*
使用例:
vector<int> seen(n, 0);
dfs_recursive(g, 0, seen);

auto comp = connected_components(g);
// comp[u] == comp[v] なら同じ連結成分
*/
