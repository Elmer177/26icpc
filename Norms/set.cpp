#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;

int main() {
    set<ll> s;

    // 挿入: O(log N)
    s.insert(10);
    s.insert(20);
    s.insert(5);

    // 検索: O(log N)
    if (s.count(20)) {
        cout << "20 is in the set" << endl;
    }

    // 二分探索 (重要): O(log N)
    auto it = s.lower_bound(10); // 10以上の最小要素
    if (it != s.end()) {
        cout << "Lower bound of 10: " << *it << endl;
    }

    // 削除: O(log N)
    s.erase(10);

    // 全要素の走査: O(N)
    for (int x : s) {
        cout << x << " "; // 5, 20 の順に出力される
    }
}
