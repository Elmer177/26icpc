#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
尺取り法の典型

非負配列で、和が K 以下の連続部分列の個数を数える。
右端 r は戻らないので O(N)。

条件が「rを伸ばすほど悪くなる」タイプなら同じ形で使える。
例: 和がK以下、種類数がK以下、最大値-最小値がK以下など。
*/
ll count_subarrays_sum_leq(const vector<ll>& a, ll k) {
    int n = (int)a.size();
    ll ret = 0;
    ll sum = 0;
    int r = 0;
    for (int l = 0; l < n; l++) {
        while (r < n && sum + a[r] <= k) {
            sum += a[r];
            r++;
        }
        ret += r - l;
        if (r == l) r++;
        else sum -= a[l];
    }
    return ret;
}

/*
注意:
この形は a[i] >= 0 のときだけ使える。
負の数がある場合は累積和 + map / Fenwick / セグ木などを考える。

使用例:
vector<ll> a = {1, 2, 1, 3};
cout << count_subarrays_sum_leq(a, 3) << "\n";
*/
