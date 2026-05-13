#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;

int main(){
    int N = 100;
    vl memo(N, -1);

    // ラムダ式によるメモ化再帰
    auto fib = [&](auto self, ll n) -> ll {
        if (n <= 1) return n;
        if (memo[n] != -1) return memo[n]; // メモチェック
        return memo[n] = self(self, n - 1) + self(self, n - 2); // 再帰呼び出し
    };

    cout << fib(fib, N) << "\n";
}
