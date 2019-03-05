#include <bits/stdc++.h>

#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define R0F(i, a) for (int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); i--)

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
#define X real()
#define Y imag()

#define INF 1e18
#define PI acos(-1)

#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define SQ(x) ((x) * (x))

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef vector<ll> vll;
typedef vector<ull> vul;
typedef complex<ld> point;
typedef complex<ld> cld;
typedef vector<cld> vcld;

#define MAXN 200000

int n, lis[MAXN + 2];
vector<pair<ll, ll>> v;
vi withLis[MAXN + 2];
vector<ll> ys;
ll t, dp[MAXN + 2];

ll cost(int i_idx, int j_idx) { return dp[i_idx] + (v[j_idx].S - v[i_idx].S) * (v[j_idx].F - v[i_idx].F); }

int beatIdx(int i_idx1, int i_idx2, int l, int lo, int hi) {
    while (lo < hi - 1) {
        int mid = (lo + hi) >> 1;
        if (cost(i_idx1, withLis[l + 1][mid]) > cost(i_idx2, withLis[l + 1][mid])) lo = mid;
        else hi = mid;
    }
    return lo + 1;
}

void update(vi& q, int j_idx) { while (sz(q) >= 2 && cost(q.back(), j_idx) > cost(q[sz(q) - 2], j_idx)) q.pop_back(); }

void pushLR(vi& q, int l, int i_idx, int lo, int hi) {
    if (!q.empty() && cost(i_idx, withLis[l + 1][lo]) > cost(q.back(), withLis[l + 1][lo])) return;
    while (sz(q) >= 2 && beatIdx(q[sz(q) - 2], i_idx, l, lo, hi) <= beatIdx(q.back(), i_idx, l, lo, hi)) q.pop_back();
    q.PB(i_idx);
}

void pushRL(vi& q, int l, int i_idx, int lo, int hi) {
    if (!q.empty() && cost(i_idx, withLis[l + 1][hi - 1]) > cost(q.back(), withLis[l + 1][hi - 1])) return;
    while (sz(q) >= 2 && beatIdx(q[sz(q) - 2], i_idx, l, lo, hi) >= beatIdx(q.back(), i_idx, l, lo, hi)) q.pop_back();
    q.PB(i_idx);
}

void solveLRSweep(int l, int iLo, int iHi, int jLo, int jHi) {
    vi q;
    FOR(j, jLo, jHi) {
        int j_idx = withLis[l + 1][j];
        update(q, j_idx);
        while (iLo < iHi && v[withLis[l][iLo]].F < v[j_idx].F) {
            pushLR(q, l, withLis[l][iLo], j, jHi);
            iLo++;
        }
        if (!q.empty()) dp[j_idx] = min(dp[j_idx], cost(q.back(), j_idx));
    }
}

void solveRLSweep(int l, int iLo, int iHi, int jLo, int jHi) {
    vi q;
    ROF(j, jLo, jHi) {
        int j_idx = withLis[l + 1][j];
        update(q, j_idx);
        while (iHi > iLo && v[withLis[l][iHi - 1]].S < v[j_idx].S) {
            pushRL(q, l, withLis[l][iHi - 1], jLo, j + 1);
            iHi--;
        }
        if (!q.empty()) dp[j_idx] = min(dp[j_idx], cost(q.back(), j_idx));
    }
}

void solveRange(int l, int iLo, int iHi, int jLo, int jHi) {
    if (jLo >= jHi) return;
    int firstNew = iLo;
    for (int i = (1 << 20); i; i >>= 1) if (firstNew + i - 1 < iHi) {
            int idx = withLis[l][firstNew + i - 1];
            if (v[idx].F < v[withLis[l + 1][jLo]].F) firstNew += i;
        }
    int lastOld = iLo - 1;
    for (int i = (1 << 20); i; i >>= 1) if (lastOld + i < iHi) {
            int idx = withLis[l][lastOld + i];
            if (v[idx].S > v[withLis[l + 1][jHi - 1]].S) lastOld += i;
        }
    solveLRSweep(l, lastOld + 1, iHi, jLo, jHi);
    solveRLSweep(l, iLo, firstNew, jLo, jHi);
}

void solve(int l) {
    int lo = 0, hi = 0;
    int initLo = 0, lastHi = 0;
    int initJ = 0;
    F0R(j, sz(withLis[l + 1])) {
        int j_idx = withLis[l + 1][j];
        while (hi < sz(withLis[l]) && v[withLis[l][hi]].F <= v[j_idx].F) hi++;
        while (lo < sz(withLis[l]) && v[withLis[l][lo]].S >= v[j_idx].S) {
            if (lo == lastHi) {
                solveRange(l, initLo, hi, initJ, j);
                initLo = lo + 1;
                lastHi = hi;
                initJ = j;
            }
            lo++;
        }
    }
    solveRange(l, initLo, hi, initJ, sz(withLis[l + 1]));
}

void solveLIS() {
    vi z(1, 0);
    lis[0] = 0;
    withLis[0].PB(0);
    
    FOR(i, 1, n) {
        int yidx = LB(all(ys), v[i].S) - ys.begin();
        lis[i] = LB(all(z), yidx) - z.begin();
        if (lis[i] == sz(z)) z.PB(yidx);
        else z[lis[i]] = min(z[lis[i]], yidx);
        withLis[lis[i]].PB(i);
    }
}

void readInput() {
    ifstream cin("mowing.in");
    cin >> n >> t;
    F0R(i, n) {
        ll x, y;
        cin >> x >> y;
        v.PB(MP(x, y));
    }
    v.PB(MP(0LL, 0LL));
    v.PB(MP(t, t));
    sort(all(v));
    n = sz(v);

    for (const pair<ll, ll> p : v) ys.PB(p.S);
    sort(all(ys));
}

int main() {
    ifstream cin("mowing.in");
    cin >> n >> t;
    F0R(i, n) {
        ll x, y;
        cin >> x >> y;
        v.PB(MP(x, y));
    }

    v.PB(MP(0LL, 0LL));
    v.PB(MP(t, t));
    sort(all(v));
    n = sz(v);

    for (const pair<ll, ll> p : v) ys.PB(p.S);
    sort(all(ys));
    
    solveLIS();
    
    FOR(i, 1, n) dp[i] = INF;
    F0R(l, lis[n - 1]) solve(l);
    ofstream cout("mowing.out");
    cout << dp[n - 1] << endl;
}
