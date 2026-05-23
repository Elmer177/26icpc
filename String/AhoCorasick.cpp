#include <bits/stdc++.h>
using namespace std;

/*
Aho-Corasick

複数パターンをまとめて検索するオートマトン。
デフォルトは 'a'..'z'。build() 後に検索する。

何をしているか:
Trie に「失敗したとき次にどこへ戻るか」の link を足したもの。
KMP を複数パターンに拡張したイメージ。
text を左から1文字ずつ読んで状態 v を進めるだけで、その位置で終わる全パターンが out に出る。

使い方:
1. add_string(pattern) で全部のパターンを入れる。
2. build() で link と足りない遷移を作る。
3. count_matches(text) か match(text) で検索する。

match の pair は {end_pos, pattern_id}。
開始位置は end_pos - pattern_length[pattern_id] + 1。
*/

template <int SIGMA = 26, char BASE = 'a'>
struct AhoCorasick {
    struct Node {
        array<int, SIGMA> next;
        int link = 0;
        vector<int> out;

        Node() {
            next.fill(-1);
        }
    };

    vector<Node> nodes;
    vector<int> pattern_length;

    AhoCorasick() : nodes(1) {}

    int char_id(char c) const {
        return c - BASE;
    }

    int add_string(const string& s) {
        int v = 0;
        for (char ch : s) {
            int c = char_id(ch);
            assert(0 <= c && c < SIGMA);
            if (nodes[v].next[c] == -1) {
                nodes[v].next[c] = (int)nodes.size();
                nodes.emplace_back();
            }
            v = nodes[v].next[c];
        }
        int id = (int)pattern_length.size();
        pattern_length.push_back((int)s.size());
        nodes[v].out.push_back(id);
        return id;
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < SIGMA; c++) {
            int to = nodes[0].next[c];
            if (to == -1) {
                nodes[0].next[c] = 0;
            } else {
                nodes[to].link = 0;
                q.push(to);
            }
        }

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            int link = nodes[v].link;
            for (int id : nodes[link].out) nodes[v].out.push_back(id);

            for (int c = 0; c < SIGMA; c++) {
                int to = nodes[v].next[c];
                if (to == -1) {
                    nodes[v].next[c] = nodes[link].next[c];
                } else {
                    nodes[to].link = nodes[link].next[c];
                    q.push(to);
                }
            }
        }
    }

    vector<pair<int, int>> match(const string& text) const {
        vector<pair<int, int>> res;
        int v = 0;
        for (int i = 0; i < (int)text.size(); i++) {
            int c = char_id(text[i]);
            if (c < 0 || c >= SIGMA) {
                v = 0;
                continue;
            }
            v = nodes[v].next[c];
            for (int id : nodes[v].out) res.push_back({i, id});
        }
        return res;
    }

    vector<int> count_matches(const string& text) const {
        vector<int> cnt(pattern_length.size());
        int v = 0;
        for (char ch : text) {
            int c = char_id(ch);
            if (c < 0 || c >= SIGMA) {
                v = 0;
                continue;
            }
            v = nodes[v].next[c];
            for (int id : nodes[v].out) cnt[id]++;
        }
        return cnt;
    }
};

/*
使用例:
AhoCorasick<> ac;
int id = ac.add_string("abc");
ac.build();
auto cnt = ac.count_matches(text);
cout << cnt[id] << "\n";

for (auto [end_pos, pattern_id] : ac.match(text)) {
    int start = end_pos - ac.pattern_length[pattern_id] + 1;
}
*/
