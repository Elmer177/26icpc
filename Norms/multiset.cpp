#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // multiset は重複を許す集合。
    // 最小/最大を保ちながら、値の追加削除をしたいときに便利。
    multiset<ll> s;
    s.insert(3);
    s.insert(3);
    s.insert(10);

    // 最小値・最大値
    ll mn = *s.begin();
    ll mx = *s.rbegin();

    // 1個だけ削除
    auto it = s.find(3);
    if (it != s.end()) s.erase(it);

    // 値3をすべて削除
    // s.erase(3);

    // x以上の最小値
    ll x = 5;
    auto lb = s.lower_bound(x);
    if (lb != s.end()) {
        ll val = *lb;
        (void)val;
    }

    // x以下の最大値
    auto ub = s.upper_bound(x);
    if (ub != s.begin()) {
        --ub;
        ll val = *ub;
        (void)val;
    }

    (void)mn;
    (void)mx;
}
