#include <bits/stdc++.h>
using namespace std;

/*
ModInt

整数を常に mod で割った余りとして扱う型。
足し算・引き算・掛け算・割り算を普通の数のように書ける。

- x.val(): 現在の値を int で取り出す
- x.pow(n): x^n
- x.inv(): x の逆元
- Combination<mint> comb(max_n): nCr/nPr/nHk を高速に計算する
*/

long long inv_gcd_for_modint(long long a, long long b) {
    a %= b;
    if (a < 0) a += b;
    long long s = b, t = a;
    long long m0 = 0, m1 = 1;
    while (t) {
        long long u = s / t;
        s -= t * u;
        m0 -= m1 * u;
        swap(s, t);
        swap(m0, m1);
    }
    if (m0 < 0) m0 += b / s;
    assert(s == 1);
    return m0;
}

template <int m>
struct StaticModInt {
    using mint = StaticModInt;
    unsigned int _v;

    static constexpr int mod() {
        return m;
    }

    StaticModInt() : _v(0) {}

    template <class T>
    StaticModInt(T v) {
        long long x = (long long)(v % (long long)m);
        if (x < 0) x += m;
        _v = (unsigned int)x;
    }

    int val() const {
        return (int)_v;
    }

    mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= m) _v -= m;
        return *this;
    }

    mint& operator-=(const mint& rhs) {
        if (_v < rhs._v) _v += m;
        _v -= rhs._v;
        return *this;
    }

    mint& operator*=(const mint& rhs) {
        _v = (unsigned long long)_v * rhs._v % m;
        return *this;
    }

    mint& operator/=(const mint& rhs) {
        return *this *= rhs.inv();
    }

    mint operator+() const {
        return *this;
    }

    mint operator-() const {
        return mint(0) - *this;
    }

    mint pow(long long n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }

    mint inv() const {
        return mint(inv_gcd_for_modint(_v, m));
    }

    friend mint operator+(mint lhs, const mint& rhs) {
        return lhs += rhs;
    }
    friend mint operator-(mint lhs, const mint& rhs) {
        return lhs -= rhs;
    }
    friend mint operator*(mint lhs, const mint& rhs) {
        return lhs *= rhs;
    }
    friend mint operator/(mint lhs, const mint& rhs) {
        return lhs /= rhs;
    }
    friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs._v != rhs._v;
    }
    friend ostream& operator<<(ostream& os, const mint& x) {
        return os << x.val();
    }
    friend istream& operator>>(istream& is, mint& x) {
        long long v;
        is >> v;
        x = mint(v);
        return is;
    }
};

using ModInt998244353 = StaticModInt<998244353>;
using ModInt1000000007 = StaticModInt<1000000007>;

template <class Mint>
struct Combination {
    vector<Mint> fact, ifact;

    Combination(int n = 0) {
        fact = {1};
        ifact = {1};
        build(n);
    }

    void build(int n) {
        int old = (int)fact.size() - 1;
        if (n <= old) return;
        fact.resize(n + 1);
        ifact.resize(n + 1);
        for (int i = old + 1; i <= n; i++) fact[i] = fact[i - 1] * i;
        ifact[n] = fact[n].inv();
        for (int i = n; i > old + 1; i--) ifact[i - 1] = ifact[i] * i;
    }

    Mint C(int n, int r) {
        if (r < 0 || n < r) return 0;
        build(n);
        return fact[n] * ifact[r] * ifact[n - r];
    }

    Mint P(int n, int r) {
        if (r < 0 || n < r) return 0;
        build(n);
        return fact[n] * ifact[n - r];
    }

    Mint H(int n, int r) {
        if (n == 0 && r == 0) return 1;
        return C(n + r - 1, r);
    }
};

/*
使用例:
using mint = ModInt998244353;
Combination<mint> comb(1000000);
cout << comb.C(n, k) << "\n";
*/
