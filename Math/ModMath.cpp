#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
整数・mod計算

mod_pow: 繰り返し二乗法 O(log n)
mod_inv: 逆元。gcd(a, mod)=1 のときだけ存在
floor_div/ceil_div: 負の数を含んでも数学的な floor/ceil になる除算
*/

ll mod_pow(ll a, ll n, ll mod) {
    ll ret = 1 % mod;
    a %= mod;
    while (n > 0) {
        if (n & 1) ret = (__int128)ret * a % mod;
        a = (__int128)a * a % mod;
        n >>= 1;
    }
    return ret;
}

ll ext_gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// ax = 1 (mod mod) の解。存在しない場合は -1。
ll mod_inv(ll a, ll mod) {
    ll x, y;
    ll g = ext_gcd(a, mod, x, y);
    if (g != 1) return -1;
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

ll floor_div(ll a, ll b) {
    assert(b > 0);
    if (a >= 0) return a / b;
    return -((-a + b - 1) / b);
}

ll ceil_div(ll a, ll b) {
    assert(b > 0);
    if (a >= 0) return (a + b - 1) / b;
    return -((-a) / b);
}

/*
使用例:
cout << mod_pow(2, 10, 1000000007) << "\n"; // 1024
cout << mod_inv(3, 1000000007) << "\n";

cout << floor_div(-3, 2) << "\n"; // -2
cout << ceil_div(-3, 2) << "\n";  // -1
*/
