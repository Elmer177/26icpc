#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    map<string, ll> m;

    // 挿入・更新: O(log N)
    m["apple"] = 100;
    m["banana"] = 200;

    // 取得: O(log N)
    cout << "Apple price: " << m["apple"] << endl;

    // 存在確認: O(log N)
    if (!m.count("cherry")) {
        cout << "Cherry not found" << endl;
    }

    // 削除: O(log N)
    m.erase("banana");

    // 走査: O(N)
    for (const auto& [key, value] : m) {
        cout << key << ": " << value << endl;
    }
}
