#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
行列累乗

線形漸化式、状態遷移DPを高速に進めたいときに使う。
N次正方行列の累乗は O(N^3 log e)。

mod が必要な場合は T を mint にするのが安全。
*/

template <class T>
using Matrix = vector<vector<T>>;

template <class T>
Matrix<T> matrix_mul(const Matrix<T>& a, const Matrix<T>& b) {
    int n = (int)a.size();
    int m = (int)b[0].size();
    int p = (int)b.size();
    Matrix<T> c(n, vector<T>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < p; k++) {
            if (a[i][k] == 0) continue;
            for (int j = 0; j < m; j++) c[i][j] += a[i][k] * b[k][j];
        }
    }
    return c;
}

template <class T>
Matrix<T> matrix_pow(Matrix<T> a, long long e) {
    int n = (int)a.size();
    Matrix<T> ret(n, vector<T>(n, 0));
    for (int i = 0; i < n; i++) ret[i][i] = 1;
    while (e > 0) {
        if (e & 1) ret = matrix_mul(ret, a);
        a = matrix_mul(a, a);
        e >>= 1;
    }
    return ret;
}

// mint でも ll でも使える。llでmodが必要なときはmintを使う方が安全。

/*
使用例: Fibonacci
Matrix<ll> a = {
    {1, 1},
    {1, 0},
};
auto p = matrix_pow(a, n);
// p[0][1] が F_n (F_0=0, F_1=1)
*/
