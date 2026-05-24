#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    stack<ll> st;

    // 要素の追加: O(1)
    st.push(10);
    st.push(20);
    st.push(30);

    // 要素の参照: O(1)
    cout << "Top element: " << st.top() << endl; // 30

    // 要素の削除: O(1)
    st.pop();

    // 全要素の走査 (popしながら): O(N)
    while (!st.empty()) {
        cout << st.top() << " "; // 20, 10 の順
        st.pop();
    }
}
