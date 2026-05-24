#include <bits/stdc++.h>
using namespace std;

/*
Trie

文字列集合の検索・prefix 個数。
デフォルトは 'a'..'z'。必要なら SIGMA と BASE を変える。

考え方:
各辺が1文字を表す木。
根から文字をたどった場所が、その prefix に対応するノードになる。

Node の意味:
- next[c]: 文字 c で進んだ先。なければ -1。
- pass: このノードを prefix として通った単語数。
- end: このノードで終わる単語数。

同じ単語を複数回 insert すると end/pass もその回数分増える。
*/

template <int SIGMA = 26, char BASE = 'a'>
struct Trie {
    struct Node {
        array<int, SIGMA> next;
        int pass = 0;
        int end = 0;

        Node() {
            next.fill(-1);
        }
    };

    vector<Node> nodes;

    Trie() : nodes(1) {}

    int char_id(char c) const {
        int x = c - BASE;
        assert(0 <= x && x < SIGMA);
        return x;
    }

    void insert(const string& s) {
        int v = 0;
        nodes[v].pass++;
        for (char ch : s) {
            int c = char_id(ch);
            if (nodes[v].next[c] == -1) {
                nodes[v].next[c] = (int)nodes.size();
                nodes.emplace_back();
            }
            v = nodes[v].next[c];
            nodes[v].pass++;
        }
        nodes[v].end++;
    }

    int find_node(const string& s) const {
        int v = 0;
        for (char ch : s) {
            int c = char_id(ch);
            if (nodes[v].next[c] == -1) return -1;
            v = nodes[v].next[c];
        }
        return v;
    }

    bool contains(const string& s) const {
        int v = find_node(s);
        return v != -1 && nodes[v].end > 0;
    }

    int count_word(const string& s) const {
        int v = find_node(s);
        return v == -1 ? 0 : nodes[v].end;
    }

    int count_prefix(const string& s) const {
        int v = find_node(s);
        return v == -1 ? 0 : nodes[v].pass;
    }
};

/*
使用例:
Trie<> trie;
trie.insert("abc");
cout << trie.contains("abc") << "\n";
cout << trie.count_prefix("ab") << "\n";
*/
