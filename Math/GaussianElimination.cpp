#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

/*
Gauss-Jordan elimination

連立一次方程式 Ax=b を解く。
long double 版と、素数 mod 版。
解が複数ある場合は自由変数を 0 にした一つの解を返す。

考え方:
拡大係数行列 [A|b] を行基本変形で階段状にする。
各列で pivot になる行を選び、その列の他の行を 0 にしていく。
最後に 0x+0y+...=非0 の行があれば解なし。

返り値:
- has_solution: 解があるか。
- rank: 独立な式の数。rank < 変数数なら解は複数ある。
- solution: 解の一例。自由変数は 0 にしている。

mod 版の注意:
mod_inv_prime を使うので mod は素数を想定。
mod が素数でない場合は逆元が存在しないことがあり、そのままでは使えない。
*/

const ld GAUSS_EPS = 1e-12L;

struct LinearEquationResult {
    bool has_solution;
    int rank;
    vector<ld> solution;
};

LinearEquationResult solve_linear_equations(vector<vector<ld>> a, vector<ld> b) {
    int n = (int)a.size();
    int m = n ? (int)a[0].size() : 0;
    vector<vector<ld>> aug(n, vector<ld>(m + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) aug[i][j] = a[i][j];
        aug[i][m] = b[i];
    }

    vector<int> where(m, -1);
    int row = 0;
    for (int col = 0; col < m && row < n; col++) {
        int sel = row;
        for (int i = row; i < n; i++) {
            if (fabsl(aug[i][col]) > fabsl(aug[sel][col])) sel = i;
        }
        if (fabsl(aug[sel][col]) < GAUSS_EPS) continue;
        swap(aug[sel], aug[row]);
        where[col] = row;

        ld div = aug[row][col];
        for (int j = col; j <= m; j++) aug[row][j] /= div;
        for (int i = 0; i < n; i++) {
            if (i == row) continue;
            ld factor = aug[i][col];
            if (fabsl(factor) < GAUSS_EPS) continue;
            for (int j = col; j <= m; j++) aug[i][j] -= factor * aug[row][j];
        }
        row++;
    }

    for (int i = 0; i < n; i++) {
        ld lhs = 0;
        for (int j = 0; j < m; j++) lhs += fabsl(aug[i][j]);
        if (lhs < GAUSS_EPS && fabsl(aug[i][m]) > GAUSS_EPS) return {false, row, {}};
    }

    vector<ld> x(m, 0);
    for (int j = 0; j < m; j++) {
        if (where[j] != -1) x[j] = aug[where[j]][m];
    }
    return {true, row, x};
}

ll safe_mod(ll x, ll mod) {
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

ll mod_pow_ll(ll a, ll e, ll mod) {
    ll r = 1 % mod;
    a = safe_mod(a, mod);
    while (e > 0) {
        if (e & 1) r = (__int128)r * a % mod;
        a = (__int128)a * a % mod;
        e >>= 1;
    }
    return r;
}

ll mod_inv_prime(ll a, ll mod) {
    return mod_pow_ll(a, mod - 2, mod);
}

struct LinearEquationModResult {
    bool has_solution;
    int rank;
    vector<ll> solution;
};

LinearEquationModResult solve_linear_equations_mod(vector<vector<ll>> a, vector<ll> b, ll mod) {
    int n = (int)a.size();
    int m = n ? (int)a[0].size() : 0;
    vector<vector<ll>> aug(n, vector<ll>(m + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) aug[i][j] = safe_mod(a[i][j], mod);
        aug[i][m] = safe_mod(b[i], mod);
    }

    vector<int> where(m, -1);
    int row = 0;
    for (int col = 0; col < m && row < n; col++) {
        int sel = -1;
        for (int i = row; i < n; i++) {
            if (aug[i][col] != 0) {
                sel = i;
                break;
            }
        }
        if (sel == -1) continue;
        swap(aug[sel], aug[row]);
        where[col] = row;

        ll inv = mod_inv_prime(aug[row][col], mod);
        for (int j = col; j <= m; j++) aug[row][j] = (__int128)aug[row][j] * inv % mod;
        for (int i = 0; i < n; i++) {
            if (i == row || aug[i][col] == 0) continue;
            ll factor = aug[i][col];
            for (int j = col; j <= m; j++) {
                aug[i][j] = safe_mod(aug[i][j] - (__int128)factor * aug[row][j] % mod, mod);
            }
        }
        row++;
    }

    for (int i = 0; i < n; i++) {
        bool all_zero = true;
        for (int j = 0; j < m; j++) all_zero &= (aug[i][j] == 0);
        if (all_zero && aug[i][m] != 0) return {false, row, {}};
    }

    vector<ll> x(m, 0);
    for (int j = 0; j < m; j++) {
        if (where[j] != -1) x[j] = aug[where[j]][m];
    }
    return {true, row, x};
}

/*
使用例:
auto res = solve_linear_equations_mod(a, b, 998244353);
if (!res.has_solution) cout << "No solution\n";
else {
    for (auto x : res.solution) cout << x << "\n";
}
*/
