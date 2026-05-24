#include <bits/stdc++.h>
using namespace std;

int main() {
    /*
    bitset<N>

    固定長 N bit の集合。N はコンパイル時定数。
    添字 i は 0-indexed で、i=0 が一番右の下位bit。

    例:
    bitset<8>("00010110")
      index: 7 6 5 4 3 2 1 0
      bit  : 0 0 0 1 0 1 1 0
    */

    bitset<8> b;              // 00000000
    bitset<8> c("00010110");  // 22。文字列の右端が bit 0
    bitset<8> d(13);          // 00001101

    // bit の確認・変更
    b.set(1);      // bit 1 を 1 にする
    b.reset(1);    // bit 1 を 0 にする
    b.flip(2);     // bit 2 を反転
    b[3] = 1;      // bit 3 を代入
    bool x = b.test(3); // b[3] と同じ。範囲外なら例外

    // 全体操作
    b.set();    // 全部 1
    b.reset();  // 全部 0
    b.flip();   // 全部反転

    // 個数・判定
    int cnt = (int)c.count(); // 1 の個数
    bool any = c.any();       // 1 が1つでもある
    bool none = c.none();     // 全部 0
    bool all = c.all();       // 全部 1
    int n = (int)c.size();    // bit 数

    // bit 演算
    bitset<8> e = c & d;
    bitset<8> f = c | d;
    bitset<8> g = c ^ d;
    bitset<8> h = ~c;
    bitset<8> left = c << 2;   // 左シフト。下位に 0 が入る
    bitset<8> right = c >> 2;  // 右シフト。上位に 0 が入る

    // 出力・数値化
    cout << c << "\n";         // 00010110
    string s = c.to_string();  // "00010110"
    unsigned long long val = c.to_ullong();

    // 立っている bit を見る
    for (int i = 0; i < (int)c.size(); i++) {
        if (c[i]) {
            cout << "bit " << i << " is on\n";
        }
    }

    /*
    よくある使いどころ:
    - N <= 数千程度の集合を高速に AND/OR したい
    - 到達可能性 DP を shift で更新したい

    例: 部分和 DP
    dp[x] = 和 x を作れるか
    a を追加すると dp |= dp << a
    */
    const int MAX_SUM = 10000;
    bitset<MAX_SUM + 1> dp;
    dp[0] = 1;
    vector<int> a = {3, 5, 8};
    for (int v : a) dp |= dp << v;
    if (dp[11]) cout << "11 can be made\n";

    // 変数長が必要なら bitset<N> は使えない。vector<int> や vector<unsigned long long> などを使う。
    (void)x;
    (void)cnt;
    (void)any;
    (void)none;
    (void)all;
    (void)n;
    (void)e;
    (void)f;
    (void)g;
    (void)h;
    (void)left;
    (void)right;
    (void)s;
    (void)val;
}
