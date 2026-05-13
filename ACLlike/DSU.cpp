#include <bits/stdc++.h>
using namespace std;

/*
Union-Find

要素をいくつかのグループに分けて管理するデータ構造。
辺を追加しながら「同じ連結成分か」「成分の大きさはいくつか」を高速に調べる。

- merge(a, b): a と b のグループを併合し、併合後の代表を返す
- same(a, b): a と b が同じグループなら true
- leader(a): a が属するグループの代表を返す
- size(a): a が属するグループの要素数を返す
- groups(): 全グループを列挙する
*/

struct DSU {
    int _n;
    vector<int> parent_or_size;

    DSU() : _n(0) {}
    explicit DSU(int n) : _n(n), parent_or_size(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    int size(int a) {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }

    vector<vector<int>> groups() {
        vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int>> result(_n);
        for (int i = 0; i < _n; i++) result[i].reserve(group_size[i]);
        for (int i = 0; i < _n; i++) result[leader_buf[i]].push_back(i);
        result.erase(remove_if(result.begin(), result.end(),
                               [](const vector<int>& v) { return v.empty(); }),
                     result.end());
        return result;
    }
};

/*
使用例:
DSU uf(n);
uf.merge(a, b);
if (uf.same(a, b)) cout << uf.size(a) << "\n";
*/
