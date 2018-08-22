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
#define X real()
#define Y imag()

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
typedef complex<ld> point;
typedef complex<ld> cld;
typedef vector<cld> vcld;

#define MAXN 100000
#define LG_MAXN 17

int n, s[MAXN], p[MAXN], mn[MAXN][LG_MAXN];
bool res[MAXN - 1];
vector<pii> v;

void constRMQ() {
    F0R(i, n) mn[i][0] = p[i] - s[i];
    F0R(j, LG_MAXN - 1) F0R(i, n) mn[i][j + 1] = min(mn[i][j], mn[min(n - 1, i + (1 << j))][j]);
}

int query(int lo, int hi) {
    if(lo > hi) return INT_MAX;
    int len = hi - lo + 1;
    int p2 = 31 - __builtin_clz(len);
    return min(mn[lo][p2], mn[hi - (1 << p2) + 1][p2]);
}

int needToPass(int i) {
    int idx = UB(p, p + n, p[i] + s[i]) - p - 1;
    int lo = i, hi = idx;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(query(mid + 1, idx) > p[i]) hi = mid;
        else lo = mid + 1;
    }
    return p[lo];
}

void solveR() {
    F0R(i, n) {
        p[i] = v[i].F;
        s[i] = v[i].S;
    }
    constRMQ();
    int req = INT_MIN;
    F0R(i, n - 1) {
        req = max(req, needToPass(i));
        if(p[i] >= req) res[i] = 1;
    }
}

int main() {
	ifstream fin("trapped.in");
	ofstream fout("trapped.out");
    fin >> n;
    F0R(i, n) {
        int a, b;
        fin >> a >> b;
        v.PB(MP(b, a));
    }
    sort(all(v));
    solveR();
    F0R(i, n) v[i].F *= -1;
    reverse(all(v));
    reverse(res, res + n - 1);
    int ans = 0;
    F0R(i, n - 1) if(!res[i]) ans += v[i + 1].F - v[i].F;
    fout << ans << endl;
}
