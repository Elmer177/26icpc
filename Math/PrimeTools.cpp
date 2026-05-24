#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
素数・約数まわり

単発なら is_prime / prime_factorization / divisors。
たくさん素因数分解するなら SmallestPrimeFactor を先に作る。
*/

bool is_prime(ll n) {
    if (n <= 1) return false;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) return false;
    }
    return true;
}

// 素因数分解: {{prime, exponent}, ...}
vector<pair<ll, int>> prime_factorization(ll n) {
    vector<pair<ll, int>> ret;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p != 0) continue;
        int e = 0;
        while (n % p == 0) {
            n /= p;
            e++;
        }
        ret.push_back({p, e});
    }
    if (n > 1) ret.push_back({n, 1});
    return ret;
}

// 約数列挙: 昇順
vector<ll> divisors(ll n) {
    vector<ll> small, large;
    for (ll d = 1; d * d <= n; d++) {
        if (n % d != 0) continue;
        small.push_back(d);
        if (d * d != n) large.push_back(n / d);
    }
    reverse(large.begin(), large.end());
    small.insert(small.end(), large.begin(), large.end());
    return small;
}

// エラトステネスの篩: n 以下の素数一覧
vector<int> sieve_primes(int n) {
    vector<bool> is_composite(n + 1, false);
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (is_composite[i]) continue;
        primes.push_back(i);
        if ((ll)i * i <= n) {
            for (ll j = (ll)i * i; j <= n; j += i) is_composite[j] = true;
        }
    }
    return primes;
}

// 最小素因数 SPF。factorize を大量に呼ぶときに使う。
struct SmallestPrimeFactor {
    vector<int> spf;

    SmallestPrimeFactor(int n) : spf(n + 1) {
        iota(spf.begin(), spf.end(), 0);
        if (n >= 0) spf[0] = 0;
        if (n >= 1) spf[1] = 1;
        for (ll i = 2; i * i <= n; i++) {
            if (spf[i] != i) continue;
            for (ll j = i * i; j <= n; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }

    vector<pair<int, int>> factorize(int x) const {
        vector<pair<int, int>> ret;
        while (x > 1) {
            int p = spf[x];
            int e = 0;
            while (x % p == 0) {
                x /= p;
                e++;
            }
            ret.push_back({p, e});
        }
        return ret;
    }
};

/*
使用例:
cout << is_prime(97) << "\n"; // true

auto pf = prime_factorization(360);
// {{2,3}, {3,2}, {5,1}}

auto ds = divisors(12);
// {1,2,3,4,6,12}

SmallestPrimeFactor spf(1000000);
auto f = spf.factorize(840);
*/
