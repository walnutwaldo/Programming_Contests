#include <bits/stdc++.h>

#define X real()
#define Y imag()

using namespace std;

typedef complex<long double> point;

int n;
vector<point> v[2], hull[2];

long double crossp(point a, point b) {
    return (conj(a) * b).imag();
}

long double dotp(point a, point b) {
    return (conj(a) * b).real();
}

vector<point> sortByAngleTo(const vector<point>& pnts, point anchor) {
    vector<pair<long double, point>> vec;
    for (const point& p : pnts) {
        if (p == anchor) { vec.emplace_back(-1, p); } else{ vec.emplace_back(arg(p - anchor), p); }
    }
    sort(vec.begin(), vec.end(),
         [anchor](const pair<long double, point>& a, const pair<long double, point>& b) -> bool {
        if (a.first != b.first) { return a.first < b.first; } else{ return abs(a.second - anchor) > abs(b.second - anchor); }
    });
    vector<point> res;
    for (const pair<long double, point> p : vec) { res.push_back(p.second); }
    return res;
}

vector<point> grahamScan(vector<point>& pnts) {
    point anchor = pnts[0];
    for (const point& p : pnts) {
        if (p.Y < anchor.Y || (p.Y == anchor.Y && p.X < anchor.X)) {
            anchor = p;
        }
    }
    pnts = sortByAngleTo(pnts, anchor);
    vector<point> res;
    for (const point& p : pnts) {
        while (res.size() >= 2 && crossp(res.back() - res[res.size() - 2], p - res.back()) < 0) { res.pop_back(); }
        while (res.size() >= 2 && crossp(res.back() - res[res.size() - 2], p - res.back()) == 0 && abs(p - res[res.size() - 2]) > abs(res.back() - res[res.size() - 2])) { res.pop_back(); }
        res.push_back(p);
    }
    while (res.size() > 2 && crossp(res.back() - res[res.size() - 2], res[0] - res.back()) == 0) {
        res.pop_back();
    }
    assert(res.size() <= 2 || crossp(res.back() - res[res.size() - 2], res[0] - res.back()) > 0);
    return res;
}

int getScore(vector<point>& h, vector<point>& pnts) {
    if (h.size() <= 3) {
        if (h.size() == 3) {
            int res = 0;
            for (const point& p : pnts) {
                if (dotp(h[1] - p, p - h[0]) > 0 && crossp(h[1] - h[0], p - h[1]) == 0) { res++; }
            }
            return res;
        } else { return 0; }
    }
    int res = 0;
    vector<point> vec;
    for (const point& p : pnts) { if (p.Y >= h[0].Y) { vec.push_back(p); } }
    vec = sortByAngleTo(vec, h[0]);
    int i = 0;
    for (int j = 0; j < vec.size(); j++) {
        while (i < h.size() - 2 && arg(vec[j] - h[0]) > arg(h[i + 1] - h[0])) { i++; }
        if (i < h.size() - 2 && arg(vec[j] - h[0]) == arg(h[i + 1] - h[0])) {
            if (i == 0) { i++; }
        }
        if (crossp(h[i + 1] - h[i], vec[j] - h[i + 1]) >= 0) {
            res++;
        }
    }
    return res;
}

int main() {
    ifstream cin("curling.in");
    ofstream cout("curling.out");
    cin >> n;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            int x, y;
            cin >> x >> y;
            v[i].push_back(point(x, y));
        }
        hull[i] = grahamScan(v[i]);
        hull[i].push_back(hull[i][0]);
    }
    cout << getScore(hull[0], v[1]) << " " << getScore(hull[1], v[0]) << endl;
    return 0;
}
