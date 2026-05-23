#include <bits/stdc++.h>
using namespace std;

/*
KMP / prefix function

文字列検索を O(|S|+|T|) で行う。
prefix_function[i] は s[0..i] の最長の proper prefix = suffix の長さ。

proper prefix は「文字列全体とは違う prefix」のこと。
pi[i] がわかると、pattern の途中まで一致して失敗したときに、
どこまで戻ればよいかを再利用できる。

使いどころ:
- text 内の pattern 出現位置を全部探す
- 文字列の周期
- prefix と suffix が一致する長さの列挙
*/

vector<int> prefix_function(const string& s) {
    int n = (int)s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

vector<int> kmp_search(const string& text, const string& pattern) {
    if (pattern.empty()) {
        vector<int> res(text.size() + 1);
        iota(res.begin(), res.end(), 0);
        return res;
    }

    vector<int> pi = prefix_function(pattern);
    vector<int> res;
    int j = 0;
    for (int i = 0; i < (int)text.size(); i++) {
        while (j > 0 && text[i] != pattern[j]) j = pi[j - 1];
        if (text[i] == pattern[j]) j++;
        if (j == (int)pattern.size()) {
            res.push_back(i - (int)pattern.size() + 1);
            j = pi[j - 1];
        }
    }
    return res;
}

/*
使用例:
for (int pos : kmp_search(text, pat)) {
    cout << pos << "\n";
}
*/
