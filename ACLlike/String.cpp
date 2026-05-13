#include <bits/stdc++.h>
using namespace std;

/*
文字列アルゴリズム

文字列の一致・辞書順・共通接頭辞を調べるための関数。
- z_algorithm: 各位置から始まる接頭辞一致長を求める
- suffix_array: 接尾辞を辞書順に並べた開始位置の列を求める
- lcp_array: suffix_array で隣り合う接尾辞どうしの共通接頭辞長を求める

suffix_array は実装の軽さ優先で O(N log^2 N) の doubling。
*/

template <class T>
vector<int> z_algorithm(const vector<T>& s) {
    int n = (int)s.size();
    if (n == 0) return {};
    vector<int> z(n);
    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (r < i + z[i]) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

vector<int> z_algorithm(const string& s) {
    vector<int> v(s.begin(), s.end());
    return z_algorithm(v);
}

template <class T>
vector<int> suffix_array(const vector<T>& s) {
    int n = (int)s.size();
    vector<int> sa(n), rnk(n), tmp(n);
    iota(sa.begin(), sa.end(), 0);
    if (n == 0) return sa;

    vector<T> xs = s;
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    for (int i = 0; i < n; i++) {
        rnk[i] = lower_bound(xs.begin(), xs.end(), s[i]) - xs.begin();
    }

    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int i, int j) {
            if (rnk[i] != rnk[j]) return rnk[i] < rnk[j];
            int ri = i + k < n ? rnk[i + k] : -1;
            int rj = j + k < n ? rnk[j + k] : -1;
            return ri < rj;
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        swap(rnk, tmp);
        if (rnk[sa[n - 1]] == n - 1) break;
    }
    return sa;
}

vector<int> suffix_array(const string& s) {
    vector<int> v(s.size());
    for (int i = 0; i < (int)s.size(); i++) v[i] = (unsigned char)s[i];
    return suffix_array(v);
}

template <class T>
vector<int> lcp_array(const vector<T>& s, const vector<int>& sa) {
    int n = (int)s.size();
    assert(n >= 1);
    vector<int> rnk(n), lcp(n - 1);
    for (int i = 0; i < n; i++) rnk[sa[i]] = i;
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (rnk[i] == 0) continue;
        int j = sa[rnk[i] - 1];
        while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
        lcp[rnk[i] - 1] = h;
        if (h > 0) h--;
    }
    return lcp;
}

vector<int> lcp_array(const string& s, const vector<int>& sa) {
    vector<int> v(s.size());
    for (int i = 0; i < (int)s.size(); i++) v[i] = (unsigned char)s[i];
    return lcp_array(v, sa);
}

/*
使用例:
auto z = z_algorithm(s);
auto sa = suffix_array(s);
auto lcp = lcp_array(s, sa);
*/
