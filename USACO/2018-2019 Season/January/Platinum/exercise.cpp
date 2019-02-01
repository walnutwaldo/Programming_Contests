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

#define MAXN 200000

int n, m, par[MAXN][18], dep[MAXN];
ll dp[MAXN];

vi adj[MAXN];
vector<pii> edges;

void dfs(int node) {
    FOR(i, 1, 18) par[node][i] = par[par[node][i - 1]][i - 1];
    for(const int next : adj[node]) if(next != par[node][0]) {
        dep[next] = dep[node] + 1;
        par[next][0] = node;
        dfs(next);
    }
}

void dfs2(int node) {
    for(const int next : adj[node]) if(next != par[node][0]) {
        dfs2(next);
        dp[node] += dp[next];
    }
}

int rise(int node, int amt) {
    F0R(i, 18) if((amt >> i) & 1) node = par[node][i];
    return node;
}

int lca(int a, int b) {
    if(dep[a] > dep[b]) a = rise(a, dep[a] - dep[b]);
    else b = rise(b, dep[b] - dep[a]);
    if(a == b) return a;
    R0F(i, 18) if(par[a][i] != par[b][i]) {
        a = par[a][i];
        b = par[b][i];
    }
    return par[a][0];
}

int main() {
    ifstream cin("exercise.in");
    ofstream cout("exercise.out");
    cin >> n >> m;
    F0R(i, n - 1) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].PB(b);
        adj[b].PB(a);
    }
    dfs(0);
    F0R(i, m - n + 1) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        edges.PB(MP(a, b));
    }
    F0R(i, sz(edges)) {
        int anc = lca(edges[i].F, edges[i].S);
        dp[edges[i].F]++, dp[edges[i].S]++;
        dp[anc] -= 2;
    }
    dfs2(0);
    ll res = 0;
    map<pii, ll> cnt;
    map<int, ll> withancp;
    F0R(i, sz(edges)) {
        int anc = lca(edges[i].F, edges[i].S);
        int ancp1 = -1, ancp2 = -1;
        if(dep[edges[i].F] > dep[anc]) ancp1 = rise(edges[i].F, dep[edges[i].F] - dep[anc] - 1);
        if(dep[edges[i].S] > dep[anc]) ancp2 = rise(edges[i].S, dep[edges[i].S] - dep[anc] - 1);
        if(ancp1 != -1) res += dp[ancp1] - 1;
        if(ancp2 != -1) res += dp[ancp2] - 1;
        if(ancp1 != -1 && ancp2 != -1) {
            pii p = MP(min(ancp1, ancp2), max(ancp1, ancp2));
            res -= cnt[p];
            cnt[p]++;
        }
        if(ancp1 != -1) {
            res -= withancp[ancp1];
            withancp[ancp1]++;
        }
        if(ancp2 != -1) {
            res -= withancp[ancp2];
            withancp[ancp2]++;
        }
    }
    cout << res << endl;
}
