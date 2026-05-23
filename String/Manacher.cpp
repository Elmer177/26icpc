#include <bits/stdc++.h>
using namespace std;

/*
Manacher

各中心の回文半径を O(N) で求める。
odd[i]: 中心 i の奇数長回文半径。s[i-r+1 .. i+r) が回文。
even[i]: i-1 と i の間を中心にした偶数長回文半径。s[i-r .. i+r) が回文。

半径の見方:
odd[i] = 1 なら s[i] だけ、2 なら長さ3、3 なら長さ5の回文。
even[i] = 0 なら空、1 なら s[i-1..i] の長さ2回文。

使いどころ:
- 最長回文部分文字列
- 各位置を中心に何個の回文があるか
- is_palindrome(l,r) で s[l..r) が回文かを O(1) 判定
*/

vector<int> manacher_odd(const string& s) {
    int n = (int)s.size();
    vector<int> d(n);
    int l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        int k = (i > r) ? 1 : min(d[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        d[i] = k;
        if (i + k - 1 > r) {
            l = i - k + 1;
            r = i + k - 1;
        }
    }
    return d;
}

vector<int> manacher_even(const string& s) {
    int n = (int)s.size();
    vector<int> d(n);
    int l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        int k = (i > r) ? 0 : min(d[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d[i] = k;
        if (i + k - 1 > r) {
            l = i - k;
            r = i + k - 1;
        }
    }
    return d;
}

bool is_palindrome(int l, int r, const vector<int>& odd, const vector<int>& even) {
    int len = r - l;
    if (len <= 0) return true;
    if (len & 1) {
        int c = (l + r) / 2;
        return odd[c] >= len / 2 + 1;
    } else {
        int c = (l + r) / 2;
        return even[c] >= len / 2;
    }
}

/*
使用例:
auto odd = manacher_odd(s);
auto even = manacher_even(s);
if (is_palindrome(l, r, odd, even)) cout << "Yes\n"; // s[l..r)
*/
