#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
#define all(v) v.begin(), v.end()

int main() {
// 昇順ソート済み配列 (n=10)
    vector<int> a = {1, 4, 4, 7, 7, 8, 8, 11, 13, 19};

    // --- lower_bound (x以上の最小の要素) ---
    auto lb1 = lower_bound(all(a), 4);  // *lb1 = 4,  idx = 1
    auto lb2 = lower_bound(all(a), 6);  // *lb2 = 7,  idx = 3
    auto lb3 = lower_bound(all(a), 20); // *lb3 = ??? (endにつき参照NG), idx = 10

    // --- upper_bound (xより大きい最小の要素) ---
    auto ub1 = upper_bound(all(a), 4);  // *ub1 = 7,  idx = 3
    auto ub2 = upper_bound(all(a), 6);  // *ub2 = 7,  idx = 3
    auto ub3 = upper_bound(all(a), 19); // *ub3 = ??? (endにつき参照NG), idx = 10

    // --- 逆引きリファレンス ---
    
    // 1. 値の確認 (a.end()チェックを忘れずに)
    // cout << (lb1 != a.end() ? to_string(*lb1) : "None");

    // 2. インデックス (先頭からの距離)
    int idx = lb1 - a.begin(); 
    // lb1: 1, lb2: 3, lb3: 10
    // ub1: 3, ub2: 3, ub3: 10

    // 3. 残りの要素数 (末尾までの距離)
    int dist = a.end() - lb1;
    // lb1: 9, lb2: 7, lb3: 0

    // 4. x の個数
    int count_4 = upper_bound(all(a), 4) - lower_bound(all(a), 4);
    // count_4: 2 (index 3 - 1)

    return 0;
}
