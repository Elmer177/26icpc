#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;

int main(){
    // 1. 最大ヒープ (大きい順に出る)
    priority_queue<ll> max_pq;
    
    // 2. 最小ヒープ (小さい順に出る)
    priority_queue<ll, vl, greater<ll>> min_pq;


    for (int x : {3, 1, 4, 1, 5}) {
        // 要素の追加: O(log N)
        max_pq.push(x);
        min_pq.push(x);
    }

    // 要素の参照: O(1)
    cout << "Max: " << max_pq.top() << endl; // 5
    cout << "Min: " << min_pq.top() << endl; // 1

    // 要素の削除: O(log N)
    max_pq.pop();
    min_pq.pop();

    // 全要素の走査 (popしながら): O(N log N)
    cout << "Max Heap: ";
    while (!max_pq.empty()) {
        cout << max_pq.top() << " "; // 4, 3, 1, 1 の順
        max_pq.pop();
    }
    
    cout << "\nMin Heap: ";
    while (!min_pq.empty()) {
        cout << min_pq.top() << " "; // 1, 3, 4, 5 の順
        min_pq.pop();
    }
}
