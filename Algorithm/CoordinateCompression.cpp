#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
座標圧縮

大きい値や負の値を、大小関係を保ったまま 0,1,2,... に変換する。
Fenwick Tree / Segment Tree / DP の添字にしたいときに使う。

build() 後:
- get(x): x が何番目に小さい値かを返す
- value(i): 圧縮後 i に対応する元の値を返す
*/
template <class T>
struct CoordinateCompression {
    vector<T> xs;

    CoordinateCompression() = default;
    CoordinateCompression(const vector<T>& v) : xs(v) { build(); }

    void add(T x) { xs.push_back(x); }

    void build() {
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
    }

    int get(T x) const {
        return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    }

    T value(int i) const { return xs[i]; }
    int size() const { return (int)xs.size(); }
};

/*
使用例:
vector<ll> a = {100, 10, 1000, 10};
CoordinateCompression<ll> comp(a);
for (ll x : a) cout << comp.get(x) << "\n"; // 1,0,2,0

// 後から値を足す場合
CoordinateCompression<ll> c;
c.add(-5);
c.add(1000000000000LL);
c.build();
cout << c.get(-5) << "\n"; // 0
*/
