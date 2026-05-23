# 26icpc
ICPCのテンプレート共有


## Others

- `base_gurukun.cpp`: gurukunのテンプレート。`ll`, `vector` alias, `rep`, `all`, `chmax/chmin`, `yn`, 入出力補助, `inside(x,y,h,w)`

## Norms

STL や構文を忘れたときに見るメモ。

- `lower_and_upper.cpp`: `lower_bound` / `upper_bound` の使い方、index取得、個数取得
- `lamda.cpp`: ラムダ式によるメモ化再帰
- `map.cpp`: `map` の挿入、取得、存在確認、削除、走査
- `multiset.cpp`: `multiset` の最小値・最大値、1個削除、全削除、`lower_bound`
- `priority_queue.cpp`: 最大ヒープ、最小ヒープ、`push/top/pop`
- `queue.cpp`: `queue` の `push/front/pop`
- `set.cpp`: `set` の挿入、検索、`lower_bound`、削除、走査
- `setprecision.cpp`: 小数出力の `fixed << setprecision(...)`
- `stack.cpp`: `stack` の `push/top/pop`
- `bit.cpp`: bit の立てる/消す/反転、`popcount`, `ctz`, 部分集合・上位集合列挙

## ACLlike

ACLもどき

- `DSU.cpp`: Union-Find。連結成分の併合、同一判定、成分サイズ
- `Fenwick.cpp`: Fenwick Tree。一点加算・区間和
- `Segment.cpp`: Segment Tree。区間最小値・区間和など、1点更新・区間取得
- `LazySegment.cpp`: Lazy Segment Tree。区間更新・区間取得
- `mint.cpp`: `ModInt998244353` / `ModInt1000000007` と `Combination`。nCr/nPr/nHk
- `Math.cpp`: `pow_mod`, `inv_mod`, `crt`, `floor_sum`
- `String.cpp`: `z_algorithm`, `suffix_array`, `lcp_array`
- `Convolution.cpp`: 畳み込み。998244353 mod の `convolution`、厳密整数の `convolution_ll`
- `SCC.cpp`: 強連結成分分解。有向グラフを互いに行き来できる頂点集合に分ける
- `TwoSAT.cpp`: 2-SAT。二択条件の充足可能性判定
- `MaxFlow.cpp`: 最大流。二部マッチングにも使う
- `MinCostFlow.cpp`: 最小費用流。割当問題、最小コストマッチング向け

## Algorithm

典型アルゴリズムと前処理。

- `BinarySearch.cpp`: めぐる式二分探索
- `CoordinateCompression.cpp`: 座標圧縮
- `CumulativeSum.cpp`: 一次元・二次元累積和
- `Imos.cpp`: 一次元・二次元 imos
- `LIS.cpp`: 最長増加部分列。狭義/広義、各位置のLIS長
- `BitDP.cpp`: subset/superset zeta・mobius 変換、集合DPのメモ
- `SubsetEnumeration.cpp`: bit の部分集合列挙
- `TwoPointers.cpp`: 尺取り法の典型。非負配列で和がK以下の区間数

## Geometry

二次元幾何。

- `Geometry2D.cpp`: `Point`, 内積/外積, `ccw`, 線分交差, 距離, 多角形面積, 点の内外判定, 凸包

## Graph

グラフ・木の頻出部品。

- `DFS.cpp`: 再帰DFS、連結成分番号
- `BFS.cpp`: unweighted graph の最短距離
- `BFS_Grid.cpp`: グリッドBFS、4近傍/8近傍方向配列
- `Dijkstra.cpp`: 非負重みグラフの単一始点最短路
- `ZeroOneBFS.cpp`: 辺重みが0/1のグラフの最短路
- `BellmanFord.cpp`: 負辺ありの単一始点最短路、負閉路の影響を受ける頂点検出
- `WarshallFloyd.cpp`: 全点対最短路、負閉路判定
- `MinimumSpanningTree.cpp`: Kruskal / Prim による最小全域木
- `LowLink.cpp`: 橋・関節点・二重辺連結成分
- `TopologicalSort.cpp`: DAG のトポロジカルソート
- `EulerTour.cpp`: 木のオイラーツアー。部分木を区間に変換
- `LCA.cpp`: 最近共通祖先、木上距離
- `HeavyLightDecomposition.cpp`: 木上パスを区間に分解。セグ木/Fenwickと組み合わせる
- `Rerooting.cpp`: 全方位木DP。全頂点を根にしたDPをO(N)で求める
- `TreeDiameter.cpp`: 木の直径
- `Bipartite.cpp`: 二部グラフ判定
- `HopcroftKarp.cpp`: 二部グラフの最大マッチング、最小点カバー

## DataStructure

データ構造・応用。

- `SparseTable.cpp`: RMQ/GCD などの静的区間クエリ。構築 O(N log N)、クエリ O(1)
- `WeightedUnionFind.cpp`: 重み付きUnion-Find。差分制約、ポテンシャル管理
- `FenwickRangeAdd.cpp`: Fenwick Tree 2本による区間加算・区間和
- `InversionNumber.cpp`: 座標圧縮 + Fenwick Tree による転倒数

## Math

整数・数論系。

- `PrimeTools.cpp`: 素数判定、素因数分解、約数列挙、エラトステネスの篩、SPF
- `ModMath.cpp`: modpow、拡張Euclid、mod逆元、floor/ceil div
- `MatrixPower.cpp`: 行列積、行列累乗。`mint` と組み合わせるとmod行列累乗になる
- `XorLinearBasis.cpp`: XOR線形基底。作れる値判定、最大XOR
- `GaussianElimination.cpp`: Gauss-Jordan 消去。実数版と素数mod版の連立一次方程式

## String

文字列処理。

- `RunLengthEncoding.cpp`: 文字列・vector のランレングス圧縮
- `RollingHash.cpp`: ローリングハッシュ。部分文字列比較向け
- `Manacher.cpp`: 各中心の回文半径、区間が回文かの判定
- `KMP.cpp`: prefix function と文字列検索
- `Trie.cpp`: 文字列集合の検索、prefix個数
- `AhoCorasick.cpp`: 複数パターンの同時検索
