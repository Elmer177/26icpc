#include <bits/stdc++.h>
using namespace std;

/*
XOR 線形基底

数列から XOR で作れる値の判定、最大 XOR 値など。
非負 long long なら LOG=62 で十分。unsigned long long で扱う。
計算量: add/can_make/max_xor は O(LOG)。

考え方:
XOR 版の掃き出し法。
basis[i] には「最上位bitが i の代表ベクトル」を1つだけ持つ。
新しい x を入れるとき、最上位bitが同じ basis があれば x ^= basis[i] でそのbitを消す。
最後に 0 にならなければ、今までの数だけでは作れない新しい値なので基底に追加できる。

使いどころ:
- 部分集合 XOR で作れるか: can_make(x)
- 部分集合 XOR の最大値: max_xor()
- グラフの閉路 XOR を基底に入れて、パス XOR の最大化をする問題

rank は独立な値の個数。作れる XOR 値の種類数は 2^rank。
*/

template <int LOG = 62>
struct XorLinearBasis {
    array<unsigned long long, LOG + 1> basis{};
    int rank = 0;

    bool add(unsigned long long x) {
        for (int i = LOG; i >= 0; i--) {
            if (((x >> i) & 1ULL) == 0) continue;
            if (basis[i] == 0) {
                basis[i] = x;
                rank++;
                return true;
            }
            x ^= basis[i];
        }
        return false;
    }

    bool can_make(unsigned long long x) const {
        for (int i = LOG; i >= 0; i--) {
            if (((x >> i) & 1ULL) == 0) continue;
            if (basis[i] == 0) return false;
            x ^= basis[i];
        }
        return true;
    }

    unsigned long long max_xor(unsigned long long start = 0) const {
        unsigned long long res = start;
        for (int i = LOG; i >= 0; i--) {
            if ((res ^ basis[i]) > res) res ^= basis[i];
        }
        return res;
    }

    void merge_from(const XorLinearBasis& other) {
        for (int i = LOG; i >= 0; i--) {
            if (other.basis[i]) add(other.basis[i]);
        }
    }

    vector<unsigned long long> vectors() const {
        vector<unsigned long long> res;
        for (int i = 0; i <= LOG; i++) {
            if (basis[i]) res.push_back(basis[i]);
        }
        return res;
    }
};

/*
使用例:
XorLinearBasis<> xb;
for (long long x : a) xb.add((unsigned long long)x);
cout << xb.max_xor() << "\n";
if (xb.can_make(target)) cout << "Yes\n";
*/
