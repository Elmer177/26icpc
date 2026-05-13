#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
LIS: 最長増加部分列

配列からいくつか要素を選び、順番を保ったまま増加列にする最大長。
計算量 O(N log N)。

strict=true  : 狭義増加 <
strict=false : 広義増加 <=
*/
template <class T>
int lis_length(const vector<T>& a, bool strict = true) {
    vector<T> dp;
    for (T x : a) {
        auto it = strict ? lower_bound(dp.begin(), dp.end(), x)
                         : upper_bound(dp.begin(), dp.end(), x);
        if (it == dp.end()) dp.push_back(x);
        else *it = x;
    }
    return (int)dp.size();
}

// 各位置を末尾にするLIS長
template <class T>
vector<int> lis_lengths_each(const vector<T>& a, bool strict = true) {
    vector<T> dp;
    vector<int> ret(a.size());
    for (int i = 0; i < (int)a.size(); i++) {
        T x = a[i];
        auto it = strict ? lower_bound(dp.begin(), dp.end(), x)
                         : upper_bound(dp.begin(), dp.end(), x);
        int len = it - dp.begin() + 1;
        if (it == dp.end()) dp.push_back(x);
        else *it = x;
        ret[i] = len;
    }
    return ret;
}

/*
使用例:
vector<int> a = {3, 1, 2, 2, 4};
cout << lis_length(a) << "\n";        // 3: 1,2,4
cout << lis_length(a, false) << "\n"; // 4: 1,2,2,4

auto left = lis_lengths_each(a);
// left[i] は「i番目を最後にするLIS長」
*/
