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

pll dp[2 * MAXN][MAXG + 1];

void comb(pll& a, const ll& b1, const ll& b2) {
    if(a.F > b1) a = MP(b1, b2);
    else if(a.F == b1) a.S = (a.S + b2) % MOD;
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

int breakHoriz[MAXG][1 << (MAXK - 1)];
int breakVert[MAXG][1 << MAXK];

void simplify(int *arr) {
    map<int, int> mp;
    int curr = 0;
    F0R(i, k) {
        if (!mp.count(arr[i]))
            mp[arr[i]] = curr++;
        arr[i] = mp[arr[i]];
    }
}

int calcBH(int *arr, int mask) {
    int *res = new int[k];
    F0R(i, k) res[i] = arr[i];
    F0R(i, k - 1) if ((mask >> i) & 1) {
        int a = res[i + 1];
        F0R(j, k) if (res[j] == a) res[j] = res[i];
    }
    simplify(res);
    return groupingID[getHash(res)];
}

int calcBV(int *arr, int mask) {
    int *res = new int[k];
    int largest = 0;
    F0R(i, k) {
        res[i] = arr[i];
        largest = max(largest, res[i]);
    }
    F0R(i, k) if (!((mask >> i) & 1))
        res[i] = ++largest;
    F0R(i, largest + 1) {
        bool found = false;
        F0R(j, k) if (res[j] == i) found = 1;
        if (!found) {
            return sz(groupings);
        }
    }
    simplify(res);
    return groupingID[getHash(res)];
}

vi validHMasks[MAXG], validVMasks[MAXG];

int main() {
    ifstream cin("escape.in");
    ofstream cout("escape.out");
    cin >> n >> k;
    F0R(i, n) F0R(j, k - 1) cin >> horizCost[i][j];
    F0R(j, k) F0R(i, n - 1) cin >> vertCost[i][j];
    genGroupings(0, 0, new int[k]);
    F0R(i, sz(groupings)) {
        F0R(j, 1 << (k - 1)) {
            breakHoriz[i][j] = calcBH(groupings[i], j);
            if(breakHoriz[i][j] != sz(groupings)) validHMasks[i].PB(j);
        }
        F0R(j, 1 << k) {
            breakVert[i][j] = calcBV(groupings[i], j);
            if(breakVert[i][j] != sz(groupings)) validVMasks[i].PB(j);
        }
    }
    
    F0R(i, 2 * n) F0R(j, sz(groupings)) dp[i][j] = MP(INF, 0);
    int *allDiff = new int[k];
    F0R(i, k) allDiff[i] = i;
    dp[0][groupingID[getHash(allDiff)]] = MP(0, 1);
    ll maskCost[1 << k];
    F0R(i, 2 * n - 1) {
        memset(maskCost, 0, sizeof(maskCost));
        if (i % 2 == 0) {
            F0R(mask, 1 << (k - 1)) F0R(tmp, k - 1) if ((mask >> tmp) & 1) maskCost[mask] += horizCost[i >> 1][tmp];
        } else
            F0R(mask, 1 << k) F0R(tmp, k) if ((mask >> tmp) & 1) maskCost[mask] += vertCost[i >> 1][tmp];
        F0R(j, sz(groupings)) if(dp[i][j].S) {
            if (i % 2 == 0)
                for(const int mask : validHMasks[j]) {
                    int newGrouping = breakHoriz[j][mask];
                    comb(dp[i + 1][newGrouping], dp[i][j].F + maskCost[mask], dp[i][j].S);
                }
            else
                for(const int mask : validVMasks[j]) {
                    int newGrouping = breakVert[j][mask];
                    comb(dp[i + 1][newGrouping], dp[i][j].F + maskCost[mask], dp[i][j].S);
                }
        }
    }
    cout << dp[2 * n - 1][0].S << "\n";
}
