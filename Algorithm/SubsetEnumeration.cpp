#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
bit の部分集合列挙

bit に立っている要素だけを使った部分集合 sub をすべて列挙する。
DP[mask] から sub を分けるときなどに使う。

列挙数は 2^(popcount(bit))。
全maskについて全部分集合を回すと合計 O(3^N)。
*/
template <class F>
void enumerate_subsets(int bit, F f) {
    int sub = bit;
    while (true) {
        f(sub);
        if (sub == 0) break;
        sub = (sub - 1) & bit;
    }
}

/*
使用例:
int bit = 0b10110;
enumerate_subsets(bit, [&](int sub) {
    // sub は bit の部分集合
});

// sub の補集合側は rest = bit ^ sub
*/
