#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
Rolling Hash

部分文字列の一致判定を O(1) で行う。
get(l, r): s[l..r-1] のハッシュ。

ハッシュなので衝突の可能性はゼロではない。
厳密解が必要な問題では、suffix_array/z_algorithm なども候補。
*/
struct RollingHash {
    static const uint64_t MOD = (1ULL << 61) - 1;
    static const uint64_t BASE = 100000007;
    vector<uint64_t> pow_base, hash;

    static uint64_t mod_add(uint64_t a, uint64_t b) {
        a += b;
        if (a >= MOD) a -= MOD;
        return a;
    }

    static uint64_t mod_mul(uint64_t a, uint64_t b) {
        __uint128_t t = (__uint128_t)a * b;
        t = (t >> 61) + (t & MOD);
        if (t >= MOD) t -= MOD;
        return (uint64_t)t;
    }

    RollingHash(const string& s) {
        int n = (int)s.size();
        pow_base.assign(n + 1, 1);
        hash.assign(n + 1, 0);
        for (int i = 0; i < n; i++) {
            pow_base[i + 1] = mod_mul(pow_base[i], BASE);
            hash[i + 1] = mod_add(mod_mul(hash[i], BASE), (unsigned char)s[i] + 1);
        }
    }

    uint64_t get(int l, int r) const {
        uint64_t ret = hash[r] + MOD - mod_mul(hash[l], pow_base[r - l]);
        if (ret >= MOD) ret -= MOD;
        return ret;
    }
};

/*
使用例:
string s = "abracadabra";
RollingHash rh(s);
if (rh.get(0, 3) == rh.get(7, 10)) {
    // "abr" == "abr"
}
*/
