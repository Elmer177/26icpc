#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
整数計算

mod付き累乗、mod逆元、中国剰余定理、floor_sum。
数論問題でよく使う小さな関数をまとめたもの。
*/

ll safe_mod(ll x, ll m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

pair<ll, ll> inv_gcd(ll a, ll b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};
    ll s = b, t = a;
    ll m0 = 0, m1 = 1;
    while (t) {
        ll u = s / t;
        s -= t * u;
        m0 -= m1 * u;
        swap(s, t);
        swap(m0, m1);
    }
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}

ll pow_mod(ll x, ll n, int m) {
    assert(0 <= n && 1 <= m);
    if (m == 1) return 0;
    unsigned int um = (unsigned int)m;
    unsigned long long y = safe_mod(x, m);
    unsigned long long r = 1;
    while (n) {
        if (n & 1) r = r * y % um;
        y = y * y % um;
        n >>= 1;
    }
    return (ll)r;
}

ll inv_mod(ll x, ll m) {
    assert(1 <= m);
    auto z = inv_gcd(x, m);
    assert(z.first == 1);
    return z.second;
}

pair<ll, ll> crt(const vector<ll>& r, const vector<ll>& m) {
    assert(r.size() == m.size());
    ll r0 = 0, m0 = 1;
    for (int i = 0; i < (int)r.size(); i++) {
        assert(1 <= m[i]);
        ll r1 = safe_mod(r[i], m[i]);
        ll m1 = m[i];
        if (m0 < m1) {
            swap(r0, r1);
            swap(m0, m1);
        }
        if (m0 % m1 == 0) {
            if (r0 % m1 != r1) return {0, 0};
            continue;
        }

        auto [g, im] = inv_gcd(m0, m1);
        ll u1 = m1 / g;
        if ((r1 - r0) % g) return {0, 0};

        ll x = (ll)((__int128)safe_mod((r1 - r0) / g, u1) * im % u1);
        __int128 nr = (__int128)r0 + (__int128)x * m0;
        m0 *= u1;
        r0 = (ll)(nr % m0);
        if (r0 < 0) r0 += m0;
    }
    return {r0, m0};
}

ll floor_sum(ll n, ll m, ll a, ll b) {
    assert(0 <= n && 1 <= m);
    __int128 ans = 0;
    if (a < 0) {
        ll a2 = safe_mod(a, m);
        ans -= (__int128)n * (n - 1) / 2 * ((a2 - a) / m);
        a = a2;
    }
    if (b < 0) {
        ll b2 = safe_mod(b, m);
        ans -= (__int128)n * ((b2 - b) / m);
        b = b2;
    }
    while (true) {
        if (a >= m) {
            ans += (__int128)(n - 1) * n * (a / m) / 2;
            a %= m;
        }
        if (b >= m) {
            ans += (__int128)n * (b / m);
            b %= m;
        }
        __int128 y_max = (__int128)a * n + b;
        if (y_max < m) break;
        n = (ll)(y_max / m);
        b = (ll)(y_max % m);
        swap(m, a);
    }
    return (ll)ans;
}

/*
使用例:
cout << pow_mod(2, 10, 1000000007) << "\n";
auto [r, mod] = crt({2, 3}, {3, 5}); // x = 8 mod 15
cout << floor_sum(n, m, a, b) << "\n";
*/
