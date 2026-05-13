#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
畳み込み

多項式や数列の積を高速に計算する。
c[k] = sum a[i] * b[k-i] を求めたいときに使う。

- convolution(a, b): 998244353 で割った余りの畳み込み
- convolution_mod<MOD, primitive_root>(a, b): NTTが使える素数mod向け
- convolution_ll(a, b): long long の厳密畳み込み
*/

ll mod_pow_ll(ll a, ll n, ll mod) {
    ll r = 1;
    a %= mod;
    if (a < 0) a += mod;
    while (n) {
        if (n & 1) r = (__int128)r * a % mod;
        a = (__int128)a * a % mod;
        n >>= 1;
    }
    return r;
}

template <int MOD, int PRIMITIVE_ROOT>
void ntt(vector<ll>& a, bool inverse) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        ll wlen = mod_pow_ll(PRIMITIVE_ROOT, (MOD - 1) / len, MOD);
        if (inverse) wlen = mod_pow_ll(wlen, MOD - 2, MOD);
        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = a[i + j];
                ll v = a[i + j + len / 2] * w % MOD;
                a[i + j] = u + v;
                if (a[i + j] >= MOD) a[i + j] -= MOD;
                a[i + j + len / 2] = u - v;
                if (a[i + j + len / 2] < 0) a[i + j + len / 2] += MOD;
                w = w * wlen % MOD;
            }
        }
    }

    if (inverse) {
        ll inv_n = mod_pow_ll(n, MOD - 2, MOD);
        for (ll& x : a) x = x * inv_n % MOD;
    }
}

template <int MOD, int PRIMITIVE_ROOT>
vector<ll> convolution_mod(const vector<ll>& a, const vector<ll>& b) {
    if (a.empty() || b.empty()) return {};
    int n = (int)a.size(), m = (int)b.size();
    if (min(n, m) <= 60) {
        vector<ll> c(n + m - 1);
        for (int i = 0; i < n; i++) {
            ll x = a[i] % MOD;
            if (x < 0) x += MOD;
            for (int j = 0; j < m; j++) {
                ll y = b[j] % MOD;
                if (y < 0) y += MOD;
                c[i + j] = (c[i + j] + x * y) % MOD;
            }
        }
        return c;
    }

    int z = 1;
    while (z < n + m - 1) z <<= 1;
    vector<ll> fa(z), fb(z);
    for (int i = 0; i < n; i++) {
        fa[i] = a[i] % MOD;
        if (fa[i] < 0) fa[i] += MOD;
    }
    for (int i = 0; i < m; i++) {
        fb[i] = b[i] % MOD;
        if (fb[i] < 0) fb[i] += MOD;
    }
    ntt<MOD, PRIMITIVE_ROOT>(fa, false);
    ntt<MOD, PRIMITIVE_ROOT>(fb, false);
    for (int i = 0; i < z; i++) fa[i] = fa[i] * fb[i] % MOD;
    ntt<MOD, PRIMITIVE_ROOT>(fa, true);
    fa.resize(n + m - 1);
    return fa;
}

template <class T>
vector<ll> convolution(const vector<T>& a, const vector<T>& b) {
    vector<ll> x(a.begin(), a.end()), y(b.begin(), b.end());
    return convolution_mod<998244353, 3>(x, y);
}

vector<ll> convolution_ll(const vector<ll>& a, const vector<ll>& b) {
    if (a.empty() || b.empty()) return {};
    const ll MOD1 = 754974721;   // 2^24 * 45 + 1, primitive root 11
    const ll MOD2 = 167772161;   // 2^25 * 5 + 1, primitive root 3
    const ll MOD3 = 469762049;   // 2^26 * 7 + 1, primitive root 3
    auto c1 = convolution_mod<754974721, 11>(a, b);
    auto c2 = convolution_mod<167772161, 3>(a, b);
    auto c3 = convolution_mod<469762049, 3>(a, b);

    ll inv_m1_mod_m2 = mod_pow_ll(MOD1, MOD2 - 2, MOD2);
    ll inv_m1m2_mod_m3 = mod_pow_ll((__int128)MOD1 * MOD2 % MOD3, MOD3 - 2, MOD3);
    __int128 m1m2 = (__int128)MOD1 * MOD2;
    __int128 mod_all = m1m2 * MOD3;
    vector<ll> res(c1.size());
    for (int i = 0; i < (int)c1.size(); i++) {
        ll x1 = c1[i];
        ll t2 = (c2[i] - x1) % MOD2;
        if (t2 < 0) t2 += MOD2;
        t2 = (__int128)t2 * inv_m1_mod_m2 % MOD2;

        __int128 x = x1 + (__int128)MOD1 * t2;
        ll t3 = (c3[i] - (ll)(x % MOD3)) % MOD3;
        if (t3 < 0) t3 += MOD3;
        t3 = (__int128)t3 * inv_m1m2_mod_m3 % MOD3;
        x += m1m2 * t3;

        if (x > mod_all / 2) x -= mod_all;
        res[i] = (ll)x;
    }
    return res;
}

/*
使用例:
vector<long long> c = convolution(a, b);    // mod 998244353
vector<long long> d = convolution_ll(a, b); // 厳密
*/
