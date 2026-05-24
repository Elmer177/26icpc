#include <bits/stdc++.h>
using namespace std;

int main() {
    /*
    next_permutation / prev_permutation

    辞書順で次の並びにする。
    全順列を列挙したいときは、最初に sort してから do-while で回す。
    返り値は「次の並びが存在したか」。最後の並びの次は昇順に戻って false。
    */

    vector<int> a = {1, 2, 3};

    // 全順列列挙。3! = 6 通り。
    sort(a.begin(), a.end());
    do {
        for (int x : a) cout << x << " ";
        cout << "\n";
    } while (next_permutation(a.begin(), a.end()));

    // 文字列でも同じ
    string s = "abc";
    sort(s.begin(), s.end());
    do {
        cout << s << "\n";
    } while (next_permutation(s.begin(), s.end()));

    /*
    重複がある場合:
    sort した状態から始めれば、同じ並びは重複して出ない。
    {1,1,2} なら 3 通り。
    */
    vector<int> b = {1, 1, 2};
    sort(b.begin(), b.end());
    do {
        for (int x : b) cout << x << " ";
        cout << "\n";
    } while (next_permutation(b.begin(), b.end()));

    // 降順に列挙したい場合は prev_permutation
    vector<int> c = {1, 2, 3};
    sort(c.rbegin(), c.rend());
    do {
        for (int x : c) cout << x << " ";
        cout << "\n";
    } while (prev_permutation(c.begin(), c.end()));

    /*
    n 個から k 個選ぶ組合せ列挙

    0/1 の配列を next_permutation する。
    choose[i] == 1 のところを選ぶ。
    */
    int n = 5, k = 3;
    vector<int> choose(n, 0);
    fill(choose.end() - k, choose.end(), 1); // 00011 から始める
    do {
        vector<int> picked;
        for (int i = 0; i < n; i++) {
            if (choose[i]) picked.push_back(i);
        }
        for (int x : picked) cout << x << " ";
        cout << "\n";
    } while (next_permutation(choose.begin(), choose.end()));

    /*
    注意:
    - sort せずに始めると「今の並び以降」しか出ない。
    - 要素数が大きいと n! で爆発する。n <= 8〜10 くらいが目安。
    - next_permutation は元の配列を書き換える。
    */
}
