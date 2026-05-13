#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    queue<ll> que;

    // 要素の追加: O(1)
    que.push(10);
    que.push(20);
    que.push(30);
    
    // 要素の参照: O(1)
    cout << "Top element: " << que.front() << endl; // 10

    // 要素の削除: O(1)
    que.pop();

    // 全要素の走査 (popしながら): O(N)
    while (!que.empty()) {
        cout << que.front() << " "; // 20, 30 の順
        que.pop();
    }
}
