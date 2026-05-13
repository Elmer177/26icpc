#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vb = vector<bool>;
#define rep(i, a, b) for (ll i = (a); i < (ll)(b); i++)
const long long INF = 1LL << 60;

// 遅延セグメント木(和)
struct LazySegmentTree_Sum {
   private:
    ll size = 1;
    vl node;
    vl lazy;
    ll init_value = 0;

   public:
    // 配列を指定して初期化
    LazySegmentTree_Sum(vl v) {
        ll sz = v.size();
        while (size < sz) size *= 2;
        node.resize(2 * size - 1, init_value);
        lazy.resize(2 * size - 1, init_value);
        rep(i, 0, sz) node[i + size - 1] = v[i];
        for (ll i = size - 2; i >= 0; i--) {
            node[i] = node[2 * i + 1] + node[2 * i + 2];
        }
    }
    // サイズのみ指定
    LazySegmentTree_Sum(ll n) : LazySegmentTree_Sum(vl(n, 0)) {}

    void eval(ll k, ll l, ll r) {
        if (lazy[k] != 0) {
            node[k] += lazy[k] * (r - l);
            if (r - l > 1) {
                lazy[2 * k + 1] += lazy[k];
                lazy[2 * k + 2] += lazy[k];
            }
            lazy[k] = 0;
        }
    }

    // 区間[a, b)にvalを加算
    void update(ll a, ll b, ll val, ll k = 0, ll l = 0, ll r = -1) {
        if (r < 0) r = size;
        eval(k, l, r);
        if (r <= a || b <= l) return;
        if (a <= l && r <= b) {
            lazy[k] += val;
            eval(k, l, r);
        } else {
            update(a, b, val, 2 * k + 1, l, (l + r) / 2);
            update(a, b, val, 2 * k + 2, (l + r) / 2, r);
            node[k] = node[2 * k + 1] + node[2 * k + 2];
        }
    }

    // 区間[a, b)の和を取得
    ll query(ll a, ll b, ll k = 0, ll l = 0, ll r = -1) {
        if (r < 0) r = size;

        eval(k, l, r);

        if (r <= a || b <= l) return 0;
        if (a <= l && r <= b) return node[k];

        ll vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
        ll vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
        return vl + vr;
    }
};

// 遅延セグメント木(最小値)
struct LazySegmentTree_Min {
   private:
    ll size = 1;
    vl node;
    vl lazy;
    vb lazyFlag;
    ll init_value = INF;

   public:
    LazySegmentTree_Min(vl v) {
        ll sz = v.size();
        while (size < sz) size *= 2;
        node.resize(2 * size - 1, init_value);
        lazy.resize(2 * size - 1, init_value);
        lazyFlag.resize(2 * size - 1, false);

        rep(i, 0, sz) node[i + size - 1] = v[i];
        for (ll i = size - 2; i >= 0; i--) {
            node[i] = min(node[2 * i + 1], node[2 * i + 2]);
        }
    }
    LazySegmentTree_Min(ll n) : LazySegmentTree_Min(vl(n, INF)) {}

    void eval(ll k, ll l, ll r) {
        if (lazyFlag[k]) {
            node[k] = lazy[k];
            if (r - l > 1) {
                lazy[2 * k + 1] = lazy[k];
                lazy[2 * k + 2] = lazy[k];
                lazyFlag[2 * k + 1] = true;
                lazyFlag[2 * k + 2] = true;
            }
            lazyFlag[k] = false;
        }
    }

    void update(ll a, ll b, ll val, ll k = 0, ll l = 0, ll r = -1) {
        if (r < 0) r = size;
        eval(k, l, r);
        if (r <= a || b <= l) return;
        if (a <= l && r <= b) {
            lazy[k] = val;
            lazyFlag[k] = true;
            eval(k, l, r);
        } else {
            update(a, b, val, 2 * k + 1, l, (l + r) / 2);
            update(a, b, val, 2 * k + 2, (l + r) / 2, r);
            node[k] = min(node[2 * k + 1], node[2 * k + 2]);
        }
    }

    ll query(ll a, ll b, ll k = 0, ll l = 0, ll r = -1) {
        if (r < 0) r = size;

        eval(k, l, r);

        if (r <= a || b <= l) return INF;
        if (a <= l && r <= b) return node[k];

        ll vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
        ll vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
        return min(vl, vr);
    }
};
