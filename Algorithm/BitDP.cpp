#include <bits/stdc++.h>
using namespace std;

/*
Bit DP / SOS DP

f[mask] を部分集合・上位集合に関してまとめる変換。
n は bit 数、f.size() == 2^n。
subset_zeta 後: f[mask] = sum g[sub] for sub subset mask
superset_zeta 後: f[mask] = sum g[sup] for mask subset sup

subset_zeta の意味:
「mask に含まれる sub 全部の値を足したい」を O(3^n) ではなく O(n 2^n) でやる。
各 bit i について、i が立っている mask に f[mask ^ (1<<i)] を足していく。
これで「i を使わない場合」の値が「i を使う場合」に流れ込む。

superset_zeta の意味:
「mask を含む sup 全部の値を足したい」ときに使う。
例えば「条件 mask を満たす集合の個数」を全 mask について求めるような場面。

mobius は zeta の逆変換。zeta でまとめた値を元に戻したいときに使う。
*/

template <class T>
void subset_zeta_transform(vector<T>& f, int n) {
    assert((long long)f.size() == (1LL << n));
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (mask & (1 << i)) f[mask] += f[mask ^ (1 << i)];
        }
    }
}

template <class T>
void subset_mobius_transform(vector<T>& f, int n) {
    assert((long long)f.size() == (1LL << n));
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (mask & (1 << i)) f[mask] -= f[mask ^ (1 << i)];
        }
    }
}

template <class T>
void superset_zeta_transform(vector<T>& f, int n) {
    assert((long long)f.size() == (1LL << n));
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if ((mask & (1 << i)) == 0) f[mask] += f[mask | (1 << i)];
        }
    }
}

template <class T>
void superset_mobius_transform(vector<T>& f, int n) {
    assert((long long)f.size() == (1LL << n));
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if ((mask & (1 << i)) == 0) f[mask] -= f[mask | (1 << i)];
        }
    }
}

/*
使用例:
vector<long long> f(1 << n);
subset_zeta_transform(f, n);
// f[mask] は mask の部分集合すべての元の値の和

// 巡回セールスマン型:
// dp[mask][v] = mask の頂点を使い、最後が v の最小コスト
// 遷移: dp[mask | (1<<to)][to] = min(dp[...], dp[mask][v] + cost[v][to])
*/
