#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

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
#define EB emplace_back
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
using namespace __gnu_pbds;

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

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define MAXN 100000
#define MOD 1000000007

int n, treePar[MAXN];
vi adj[MAXN];
pii nextDown[MAXN];
vpii withLen[MAXN + 1];

ll fact[MAXN + 1];

void dfs(int node, int par = -1) {
    vpii nexts;
    treePar[node] = par;
    for (auto next : adj[node]) {
        if (next != par) {
            dfs(next, node);
            nexts.PB(nextDown[next]);
        }
    }
    if (nexts.size() == 1) {
        nextDown[node] = { nexts[0].F + 1, nexts[0].S };
    } else {
        nextDown[node] = { 0, node };
    }
    if (nexts.size() > 1 || par == -1) {
        for (const int next : adj[node]) {
            if (next != par) {
                withLen[nextDown[next].F + 1].EB(node, nextDown[next].S);
            }
        }
    }
    
}

void assign_mmult(ll& a, ll b) { a = (a * b) % MOD; }
ll mmult(ll a, ll b) { return (a * b) % MOD; }
ll modPow(ll a, ll p) { return p ? ((p & 1) ? mmult(a, modPow(a, p ^ 1)) : modPow(mmult(a, a), p >> 1)) : 1; }

int par[MAXN];
int ss[MAXN];
int y[MAXN];
set<int> roots;

int root(int node) {
    return (node == par[node]) ? node : par[node] = root(par[node]);
}

void merge(int u, int v, int toadd) {
    int r1 = root(u), r2 = root(v);
    if (ss[r1] < ss[r2]) { swap(r1, r2); }
    par[r2] = r1;
    ss[r1] += ss[r2] + toadd;
    y[r1] += y[r2] - 2;
    roots.erase(r2);
}

ll valFor(int u, int k) {
    int r = root(u);
    assert((n - 1 - k) * (y[r] - 1) + (ss[r] - 1) <= n);
    
    ll ret = fact[(n - 1 - k) * (y[r] - 1) + (ss[r] - 1)];
    return ret;
}

int main() {
    ifstream cin("circus.in");
    ofstream cout("circus.out");
    cin >> n;
    fact[0] = 1;
    FOR(i, 1, n + 1) fact[i] = mmult(fact[i - 1], i);
    F0R(i, n - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].PB(v);
        adj[v].PB(u);
    }
    int strt = 0;
    F0R(i, n) if (adj[i].size() != 2) { strt = i; }
    dfs(strt);
    F0R(i, n) if (adj[i].size() != 2) {
        par[i] = i;
        ss[i] = 1;
        y[i] = adj[i].size();
        roots.insert(i);
    }
    vll res(n + 1, fact[n]);
    ROF(k, 1, n) {
        int adjLen = n - 1 - (k + 1);
        res[k] = fact[k];
        for (const pii p : withLen[adjLen]) {
            int u = p.F, v = p.S;
            merge(u, v, adjLen - 1);
        }
        for (const int i : roots) { assign_mmult(res[k], modPow(valFor(i, k), MOD - 2)); }
    }
    FOR(k, 1, n + 1) cout << res[k] << "\n";
}
