#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
bit 演算メモ

i 番目の bit は 0-indexed。
1<<i は int なので、i が大きいときは 1LL<<i や 1ULL<<i を使う。
*/

bool has_bit(ll mask, int i) {
    return (mask >> i) & 1LL;
}

ll set_bit(ll mask, int i) {
    return mask | (1LL << i);
}

ll clear_bit(ll mask, int i) {
    return mask & ~(1LL << i);
}

ll flip_bit(ll mask, int i) {
    return mask ^ (1LL << i);
}

int popcount_ll(ll mask) {
    return __builtin_popcountll((unsigned long long)mask);
}

int lowest_bit_index(unsigned long long mask) {
    assert(mask != 0);
    return __builtin_ctzll(mask);
}

unsigned long long lowest_bit(unsigned long long mask) {
    return mask & -mask;
}

/*
よく使う書き方:

// 0..2^n-1 の全 bit
for (int mask = 0; mask < (1 << n); mask++) {}

// mask に立っている bit だけ見る
for (int b = mask; b; b &= b - 1) {
    int i = __builtin_ctz(b);
}

// mask の部分集合 sub を全部見る。空集合も含む。
for (int sub = mask;; sub = (sub - 1) & mask) {
    // sub
    if (sub == 0) break;
}

// n bit 全体の中で、mask を含む上位集合 sup を全部見る。
for (int sup = mask; sup < (1 << n); sup = (sup + 1) | mask) {
    // sup
}

// x が 2 の冪かどうか
bool power_of_two = (x > 0 && (x & (x - 1)) == 0);
*/
