#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
めぐる式二分探索

ok: 必ず条件を満たす値
ng: 必ず条件を満たさない値
is_ok(x): x が条件を満たすなら true

単調性が必要:
true true true false false のように、どこかで一度だけ切り替わる条件に使う。
計算量 O(log |ok-ng| * is_okの計算量)。
*/
template <class F>
ll binary_search_ll(ll ok, ll ng, F is_ok) {
    while (abs(ok - ng) > 1) {
        ll mid = ok + (ng - ok) / 2;
        if (is_ok(mid)) ok = mid;
        else ng = mid;
    }
    return ok;
}

/*
使用例:

// 条件を満たす最小値を探すなら、okを右側、ngを左側に置く。
auto is_ok = [&](ll x) -> bool {
    return ...;
};
ll ans = binary_search_ll(OK側, NG側, is_ok);

例: 0以上1e18以下で、x*x >= N となる最小のx
ll ans = binary_search_ll((ll)4e9, -1, [&](ll x) {
    return x >= (N + x - 1) / x;
});
*/
