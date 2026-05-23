#include <bits/stdc++.h>
using namespace std;

/*
二次元幾何

Point, 内積/外積, ccw, 線分交差, 距離, 多角形面積, 点の内外判定, 凸包。
誤差が気になる問題では EPS を調整する。

基本の見方:
- Point はベクトルとしても使う。b-a は「a から b へ向かうベクトル」。
- dot(a,b) > 0 ならなす角は鋭角、=0 なら直角、<0 なら鈍角。
- cross(a,b) > 0 なら a から b へ反時計回り、<0 なら時計回り。
- ccw(a,b,c) は「線分 ab に対して c がどちら側か」をまとめて判定する。

整数座標だけなら long double のままでもだいたい大丈夫。
厳密な整数判定だけで済む問題では Point の型を long long に変える選択肢もある。
*/

using ld = long double;
const ld GEOM_EPS = 1e-12L;
const ld GEOM_PI = acosl(-1.0L);

int sgn(ld x) {
    if (x > GEOM_EPS) return 1;
    if (x < -GEOM_EPS) return -1;
    return 0;
}

bool eq(ld a, ld b) {
    return sgn(a - b) == 0;
}

struct Point {
    ld x, y;

    Point() : x(0), y(0) {}
    Point(ld x, ld y) : x(x), y(y) {}

    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator*(ld k) const { return Point(x * k, y * k); }
    Point operator/(ld k) const { return Point(x / k, y / k); }
    bool operator<(const Point& p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
};

ld dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

ld cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

ld norm(Point p) {
    return dot(p, p);
}

ld length(Point p) {
    return sqrtl(norm(p));
}

Point rotate(Point p, ld rad) {
    ld c = cosl(rad), s = sinl(rad);
    return Point(c * p.x - s * p.y, s * p.x + c * p.y);
}

/*
ccw(a,b,c)
  1: a->b から見て c が反時計回り
 -1: 時計回り
  2: c-a-b の順に同一直線
 -2: a-b-c の順に同一直線
  0: c が線分 ab 上
*/
int ccw(Point a, Point b, Point c) {
    Point ab = b - a, ac = c - a;
    if (sgn(cross(ab, ac)) > 0) return 1;
    if (sgn(cross(ab, ac)) < 0) return -1;
    if (sgn(dot(ab, ac)) < 0) return 2;
    if (sgn(norm(ab) - norm(ac)) < 0) return -2;
    return 0;
}

bool parallel(Point a, Point b, Point c, Point d) {
    return sgn(cross(b - a, d - c)) == 0;
}

bool orthogonal(Point a, Point b, Point c, Point d) {
    return sgn(dot(b - a, d - c)) == 0;
}

bool on_segment(Point a, Point b, Point p) {
    return ccw(a, b, p) == 0;
}

bool intersect_ss(Point a, Point b, Point c, Point d) {
    return ccw(a, b, c) * ccw(a, b, d) <= 0 &&
           ccw(c, d, a) * ccw(c, d, b) <= 0;
}

Point projection(Point a, Point b, Point p) {
    Point base = b - a;
    assert(sgn(norm(base)) != 0);
    return a + base * (dot(p - a, base) / norm(base));
}

Point reflection(Point a, Point b, Point p) {
    return projection(a, b, p) * 2 - p;
}

ld dist_pp(Point a, Point b) {
    return length(a - b);
}

ld dist_lp(Point a, Point b, Point p) {
    return fabsl(cross(b - a, p - a)) / length(b - a);
}

ld dist_sp(Point a, Point b, Point p) {
    if (sgn(dot(b - a, p - a)) < 0) return dist_pp(a, p);
    if (sgn(dot(a - b, p - b)) < 0) return dist_pp(b, p);
    return dist_lp(a, b, p);
}

ld dist_ll(Point a, Point b, Point c, Point d) {
    return parallel(a, b, c, d) ? dist_lp(a, b, c) : 0;
}

ld dist_ls(Point a, Point b, Point c, Point d) {
    if (sgn(cross(b - a, c - a)) * sgn(cross(b - a, d - a)) <= 0) return 0;
    return min(dist_lp(a, b, c), dist_lp(a, b, d));
}

ld dist_ss(Point a, Point b, Point c, Point d) {
    if (intersect_ss(a, b, c, d)) return 0;
    return min({dist_sp(a, b, c), dist_sp(a, b, d), dist_sp(c, d, a), dist_sp(c, d, b)});
}

Point line_intersection(Point a, Point b, Point c, Point d) {
    assert(!parallel(a, b, c, d));
    ld t = cross(d - c, c - a) / cross(d - c, b - a);
    return a + (b - a) * t;
}

ld polygon_area2(const vector<Point>& p) {
    int n = (int)p.size();
    ld res = 0;
    for (int i = 0; i < n; i++) res += cross(p[i], p[(i + 1) % n]);
    return res;
}

ld polygon_area(const vector<Point>& p) {
    return fabsl(polygon_area2(p)) / 2;
}

/*
点が多角形のどこにあるか。
  2: 内部, 1: 辺上, 0: 外部
多角形の頂点は時計回り/反時計回りどちらでもよい。
*/
int contains_point(const vector<Point>& poly, Point p) {
    bool in = false;
    int n = (int)poly.size();
    for (int i = 0; i < n; i++) {
        Point a = poly[i] - p, b = poly[(i + 1) % n] - p;
        if (sgn(cross(a, b)) == 0 && sgn(dot(a, b)) <= 0) return 1;
        if (a.y > b.y) swap(a, b);
        if (sgn(a.y) < 0 && sgn(b.y) > 0 && sgn(cross(a, b)) > 0) in = !in;
    }
    return in ? 2 : 0;
}

/*
凸包。返り値は反時計回り。
境界上の一直線の点は除く。残したい場合は while の <= を < に変える。
*/
vector<Point> convex_hull(vector<Point> ps) {
    sort(ps.begin(), ps.end());
    ps.erase(unique(ps.begin(), ps.end(), [](Point a, Point b) {
                 return eq(a.x, b.x) && eq(a.y, b.y);
             }),
             ps.end());
    int n = (int)ps.size();
    if (n <= 2) return ps;

    vector<Point> ch;
    for (int i = 0; i < n; i++) {
        while ((int)ch.size() >= 2 &&
               sgn(cross(ch.back() - ch[(int)ch.size() - 2], ps[i] - ch.back())) <= 0) {
            ch.pop_back();
        }
        ch.push_back(ps[i]);
    }
    int lower_size = (int)ch.size();
    for (int i = n - 2; i >= 0; i--) {
        while ((int)ch.size() > lower_size &&
               sgn(cross(ch.back() - ch[(int)ch.size() - 2], ps[i] - ch.back())) <= 0) {
            ch.pop_back();
        }
        ch.push_back(ps[i]);
    }
    ch.pop_back();
    return ch;
}

/*
使用例:
Point a(0, 0), b(2, 0), c(1, 1), d(1, -1);
bool ok = intersect_ss(a, b, c, d);
auto hull = convex_hull(points);
cout << fixed << setprecision(15) << polygon_area(hull) << "\n";
*/
