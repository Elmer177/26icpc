#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
ランレングス圧縮

連続する同じ値を {値, 個数} にまとめる。
文字列の連続ブロック、同じ値の区間処理で使う。
計算量 O(N)。
*/
template <class T>
vector<pair<T, int>> run_length_encoding(const vector<T>& a) {
    vector<pair<T, int>> ret;
    for (T x : a) {
        if (ret.empty() || ret.back().first != x) ret.push_back({x, 1});
        else ret.back().second++;
    }
    return ret;
}

/*
使用例:
auto v = run_length_encoding(string("aaabbc"));
// {{'a',3}, {'b',2}, {'c',1}}

vector<int> a = {1, 1, 2, 2, 2, 1};
auto r = run_length_encoding(a);
*/

vector<pair<char, int>> run_length_encoding(const string& s) {
    vector<pair<char, int>> ret;
    for (char c : s) {
        if (ret.empty() || ret.back().first != c) ret.push_back({c, 1});
        else ret.back().second++;
    }
    return ret;
}
