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

#define MOD 1000000007
#define MAXN 1500
#define MAXC 2500

int n, m, f, x, y, target, numComp;
vector<pii> adj[MAXN];
vi compData[MAXN / 2];
ll compSum[MAXN / 2], compCnt[MAXN / 2];
ll dp[MAXN / 2 + 1][MAXC + 1];
bool inComp[MAXN];

ll modPow(ll a, ll p) { return p?((p&1)? a * modPow(a, p ^ 1) % MOD : modPow(a * a % MOD, p >> 1)):1; }

void mmult(ll& a, ll b) { a = (a * b) % MOD; }

void madd(ll& a, ll b) { a = (a + b) % MOD; }

void msub(ll& a, ll b) { a = (a + MOD - b) % MOD; }

ll fact(ll a) {
    ll res = 1;
    FOR(i, 1, a + 1) mmult(res, i);
    return res;
}

void dfsDis(int node, int compNum, ll dis, int par) {
    if(dis < target && par != -1) compData[compNum][dis]++;
    madd(compSum[compNum], dis);
    for(const pii next : adj[node]) if(next.F != par)
        dfsDis(next.F, compNum, dis + next.S, node);
}

int dfsComp(int node, int compNum, int par) {
    dfsDis(node, compNum, 0, -1);
    inComp[node] = 1;
    int nodecnt = 1;
    for(const pii next : adj[node]) if(next.F != par)
        nodecnt += dfsComp(next.F, compNum, node);
    if(par == -1) {
        compCnt[compNum] = nodecnt * (nodecnt - 1) / 2;
        mmult(compSum[compNum], 500000004LL);
        for(int& i : compData[compNum]) i /= 2;
    }
    return nodecnt;
}

int main() {
    ifstream cin("mooriokart.in");
    ofstream cout("mooriokart.out");
    cin >> n >> m >> x >> y;
    f = n - m;
    target = max(0, y - f * x);
    F0R(i, m) {
        int a, b, d;
        cin >> a >> b >> d;
        a--, b--;
        adj[a].PB(MP(b, d));
        adj[b].PB(MP(a, d));
    }
    F0R(i, n) if(!inComp[i]) {
        compData[numComp] = vi(target);
        dfsComp(i, numComp++, -1);
    }

    ll totalCnt = 1;
    F0R(i, f) mmult(totalCnt, compCnt[i]);
    ll totalSum = f * x % MOD * totalCnt % MOD;
    F0R(i, f) madd(totalSum, compSum[i] * totalCnt % MOD * modPow(compCnt[i], MOD - 2) % MOD);

    dp[0][0] = 1;
    F0R(i, f) F0R(k, target) if(compData[i][k]) F0R(j, target) if(j + k < target) madd(dp[i + 1][j + k], dp[i][j] * compData[i][k] % MOD);
    F0R(i, target) msub(totalSum, dp[f][i] * (i + f * x) % MOD);

    cout << totalSum * fact(f - 1) % MOD * modPow(2, f - 1) % MOD << endl;
}
