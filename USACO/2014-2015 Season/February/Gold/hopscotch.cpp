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

#define MOD 1000000007
#define MAXN 750

int r, c, k, grid[MAXN][MAXN];
vi occ[MAXN * MAXN];
vll totalCnt(MAXN + 1), cnt[MAXN * MAXN];

void madd(ll& a, ll b) { a = (a + b) % MOD; }

void msub(ll& a, ll b) { a = (a + MOD - b) % MOD; }

void setValue(int row, int col, ll v) {
    int x = grid[row][col];
    for(int idx = UB(all(occ[x]), col) - occ[x].begin(); idx <= sz(occ[x]); idx += idx & -idx) madd(cnt[x][idx], v);
    for(int idx = col + 1; idx <= c; idx += idx & -idx) madd(totalCnt[idx], v);
}

ll getPrefix(int col, int x) {
    ll res = 0;
    for(int idx = col + 1; idx; idx -= idx & -idx) madd(res, totalCnt[idx]);
    for(int idx = UB(all(occ[x]), col) - occ[x].begin(); idx; idx -= idx & -idx) msub(res, cnt[x][idx]);
    return res;
}

int main() {
    ifstream fin("hopscotch.in");
    ofstream fout("hopscotch.out");
    fin >> r >> c >> k;
    F0R(i, r) F0R(j, c) {
        fin >> grid[i][c - 1 - j];
        grid[i][c - 1 - j]--;
        occ[grid[i][c - 1 - j]].PB(c - 1 - j);
    }
    F0R(i, k) {
        sort(all(occ[i]));
        occ[i].erase(unique(all(occ[i])), occ[i].end());
        cnt[i] = vll(sz(occ[i]) + 1);
    }
    setValue(r - 1, 0, 1);
    ROF(i, 1, r - 1) ROF(j, 1, c - 1) setValue(i, j, getPrefix(j - 1, grid[i][j]));
    fout << getPrefix(c - 2, grid[0][c - 1]) << endl;
}
