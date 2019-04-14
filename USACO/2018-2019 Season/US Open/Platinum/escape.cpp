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

#define INF (ll)(1e18)
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

#define MOD 1000000007

#define MAXN 30000
#define MAXK 6
#define MAXG 132

int n, k;

ll horizCost[MAXN][MAXK - 1];
ll vertCost[MAXN - 1][MAXK];
int groupingID[46656];
vector<int *> groupings;

pll dp[2][MAXG];

void comb(pll& a, const ll& b1, const ll& b2) {
    if (a.F > b1) a = MP(b1, b2);
    else if (a.F == b1) a.S = (a.S + b2) % MOD;
}

bool valid(int *arr) {
    F0R(a, k) FOR(b, a + 1, k) FOR(c, b + 1, k) FOR(d, c + 1, k) if (arr[a] == arr[c] && arr[b] == arr[d] && arr[a] != arr[b]) return false;
    return true;
}

int getHash(int *arr) {
    int hash = 0;
    R0F(i, k) {
        hash *= k;
        hash += arr[i];
    }
    return hash;
}

void genGroupings(int curr, int numGroups, int *arr) {
    if (curr == k) {
        if (valid(arr)) {
            groupingID[getHash(arr)] = groupings.size();
            int *cp = new int[k];
            F0R(i, k) cp[i] = arr[i];
            groupings.PB(cp);
        }
        return;
    }
    F0R(i, numGroups + 1) {
        arr[curr] = i;
        genGroupings(curr + 1, max(numGroups, i + 1), arr);
    }
}

int addNew[MAXG][MAXK], breakH[MAXG][MAXK];

void simplify(int *arr) {
    int newID[k];
    F0R(i, k) newID[i] = -1;
    int curr = 0;
    F0R(i, k) {
        if (newID[arr[i]] == -1) newID[arr[i]] = curr++;
        arr[i] = newID[arr[i]];
    }
}

int getBreakH(int *arr, int idx) {
    int res[k];
    int oldID = arr[idx];
    F0R(i, k) res[i] = arr[i];
    F0R(i, k) if (res[i] == oldID) res[i] = arr[idx - 1];
    simplify(res);
    return groupingID[getHash(res)];
}

int getAddNew(int *arr, int idx) {
    int res[k];
    F0R(i, k) res[i] = arr[i];
    bool works = false;
    F0R(i, k) if (i != idx && res[i] == res[idx]) works = true;
    if (!works) return (int)sz(groupings);
    
    bool used[k];
    memset(used, 0, sizeof(used));
    F0R(i, k) used[arr[i]] = 1;
    int firstUnused;
    for (firstUnused = 0; used[firstUnused]; firstUnused++);
    res[idx] = firstUnused;
    simplify(res);
    return groupingID[getHash(res)];
}

vector<pii> v[MAXG][MAXK];

int main() {
    ifstream cin("escape.in");
    ofstream cout("escape.out");
    cin >> n >> k;
    F0R(i, n) F0R(j, k - 1) cin >> horizCost[i][j];
    F0R(j, k) F0R(i, n - 1) cin >> vertCost[i][j];
    genGroupings(0, 0, new int[k]);
    F0R(i, 2) F0R(g, sz(groupings)) dp[i][g] = MP(INF, 0);
    F0R(g, sz(groupings)) F0R(i, k) {
        if (i > 0) breakH[g][i] = getBreakH(groupings[g], i);
        addNew[g][i] = getAddNew(groupings[g], i);
    }
    F0R(mask, 1 << (k - 1)) {
        int arr[k];
        arr[0] = 0;
        ll cost = 0;
        FOR(i, 1, k) {
            arr[i] = arr[i - 1] + ((mask >> (i - 1)) & 1);
            if (arr[i] == arr[i - 1]) cost += horizCost[0][i - 1];
        }
        int g = groupingID[getHash(arr)];
        comb(dp[0][g], cost, 1);
    }
    F0R(g, sz(groupings)) F0R(j, k) F0R(mask, 4) {
        int newG = g;
        if (!(mask & 1)) newG = addNew[newG][j];
        if (newG == sz(groupings)) continue;
        if (mask & 2) {
            if (j == 0) continue;
            newG = breakH[newG][j];
        }
        if (newG == sz(groupings)) continue;
        v[g][j].PB(MP(newG, mask));
    }
    int curr = 0;
    FOR(t, k, (n - 1) * k + k) {
        int newI = t / k;
        int newJ = t % k;
        F0R(g, sz(groupings)) if (dp[curr][g].S) {
            for (const pii p : v[g][newJ]) {
                ll cost = 0;
                if (p.S & 1) cost += vertCost[newI - 1][newJ];
                if (p.S & 2) cost += horizCost[newI][newJ - 1];
                comb(dp[curr ^ 1][p.F], dp[curr][g].F + cost, dp[curr][g].S);
            }
            dp[curr][g] = MP(INF, 0);
        }
        curr ^= 1;
    }
    cout << dp[curr][0].S << endl;
}
