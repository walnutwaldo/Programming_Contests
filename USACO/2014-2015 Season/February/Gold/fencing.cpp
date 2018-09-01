#include <bits/stdc++.h>

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define ran() (rand() & 0x7FFF)
#define rand31() ((ran() << 16) | (ran() << 1) | (ran() & 1))
#define rand32() ((ran() << 17) | (ran() << 2) | (ran() & 3))
#define rand63() (((ll)ran() << 48) | ((ll)ran() << 33) | ((ll)ran() << 18) | ((ll)ran() << 3) | ((ll)ran() & 7))
#define rand64() (((ll)ran() << 49) | ((ll)ran() << 34) | ((ll)ran() << 19) | ((ll)ran() << 4) | ((ll)ran() & 15))

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define X first
#define Y second

#define PI acos(-1)

#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define SQ(x) ((x) * (x))

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef vector<ll> vll;
typedef vector<ull> vul;
typedef pair<ll, ll> point;
typedef complex<ld> cld;
typedef vector<cld> vcld;

#define MAXN 100000

const int HULLS = 9;

int n, q, highestP[HULLS], maxCap[HULLS]{799, 800, 1600, 3200, 64000, 12800, 25600, 51200, 102400};
vector<point> hull[HULLS];
vector<pair<ld, point>> v;

point operator-(point a, point b) {
    return MP(a.X - b.X, a.Y - b.Y);
}

ld getAngle(point p) { return atan2(p.Y, p.X); }

ll cross(point a, point b) {return a.X * b.Y - a.Y * b.X; }

void grahamScan(int i) {
    hull[i - 1].insert(hull[i - 1].end(), all(hull[i]));
    hull[i].clear();
    int minI = 0;
    F0R(j, sz(hull[i - 1])) if(hull[i - 1][j].Y < hull[i - 1][minI].Y || hull[i - 1][j].Y == hull[i - 1][minI].Y && hull[i - 1][j].X < hull[i - 1][minI].X) minI = j;
    v.clear();
    F0R(j, sz(hull[i - 1])) if(j != minI) v.PB(MP(getAngle(hull[i - 1][j] - hull[i - 1][minI]), hull[i - 1][j]));
    sort(all(v));
    hull[i].PB(hull[i - 1][minI]);
    F0R(j, sz(v)) {
        while(sz(hull[i]) > 1 && cross(hull[i].back() - hull[i][sz(hull[i]) - 2], v[j].S - hull[i].back()) <= 0) hull[i].pop_back();
        hull[i].PB(v[j].S);
    }
    highestP[i] = 0;
    F0R(j, sz(hull[i])) if(hull[i][j].Y > hull[i][highestP[i]].Y) highestP[i] = j;
    hull[i].PB(hull[i - 1][minI]);
    hull[i - 1].clear();
}

ll valOf(point p, ll A, ll B, ll C) { return A * p.X + B * p.Y - C; }

ll getHullMin(int i, ll A, ll B, ll C) {
    int lo = highestP[i], hi = sz(hull[i]) - 1;
    ll res = (1LL << 63) - 1;
    if(hull[i].empty()) return res;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        ll l = valOf(hull[i][mid], A, B, C);
        ll r = valOf(hull[i][mid + 1], A, B, C);
        res = min(res, min(l, r));
        if(l < r) hi = mid - 1;
        else lo = mid + 2;
    }
    if(lo == hi) res = min(res, valOf(hull[i][lo], A, B, C));
    return res;
}

ll getHullMax(int i, ll A, ll B, ll C) {
    int lo = 0, hi = highestP[i];
    ll res = 1LL << 63;
    if(hull[i].empty()) return res;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        ll l = valOf(hull[i][mid], A, B, C);
        ll r = valOf(hull[i][mid + 1], A, B, C);
        res = max(res, max(l, r));
        if(l > r) hi = mid - 1;
        else lo = mid + 2;
    }
    if(lo == hi) res = max(res, valOf(hull[i][lo], A, B, C));
    return res;
}

int main() {
    ifstream fin("fencing.in");
    ofstream fout("fencing.out");
    fin >> n >> q;
    F0R(i, n) {
        ll x, y;
        fin >> x >> y;
        hull[0].PB(MP(x, y));
        F0R(j, 9) if(sz(hull[j]) > maxCap[j]) grahamScan(j + 1);
    }
    F0R(i, q) {
        int cmd;
        fin >> cmd;
        if(cmd == 1) {
            ll x, y;
            fin >> x >> y;
            hull[0].PB(MP(x, y));
            F0R(j, HULLS) if(sz(hull[j]) > maxCap[j]) grahamScan(j + 1);
        } else {
            ll A, B, C;
            fin >> A >> B >> C;
            if(A < 0) {
                A = -A; B = -B; C = -C;
            }
            ll mn = (1LL << 63) - 1, mx = 1LL << 63;
            for(const point p : hull[0]) {
                mn = min(mn, valOf(p, A, B, C));
                mx = max(mx, valOf(p, A, B, C));
            }
            FOR(j, 1, HULLS) {
                mn = min(mn, getHullMin(j, A, B, C));
                mx = max(mx, getHullMax(j, A, B, C));
            }
            if(mn < 0 && mx < 0 || mn > 0 && mx > 0) fout << "YES\n";
            else fout << "NO\n";
        }
    }
}
