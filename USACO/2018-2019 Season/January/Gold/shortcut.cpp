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

#define MAXN 10000

struct candidate {

    ll dis;
    int node;
    int par;

    bool operator<(const candidate& c) const {
        if(dis != c.dis) return dis > c.dis;
        return par > c.par;
    }

};

int n, m, par[MAXN];
ll t, c[MAXN], dis[MAXN];
bool vis[MAXN];
vector<pair<int, ll>> adj[MAXN];
vi children[MAXN];

ll solve(int node) {
    ll res = 0;
    for(const int next : children[node]) {
        res = max(res, solve(next));
        c[node] += c[next];
    }
    res = max(res, c[node] * (dis[node] - t));
    return res;
}

int main() {
    ifstream cin("shortcut.in");
    ofstream cout("shortcut.out");
    cin >> n >> m >> t;
    F0R(i, n) cin >> c[i];
    F0R(i, m) {
        int a, b;
        ll tt;
        cin >> a >> b >> tt;
        a--, b--;
        adj[a].PB(MP(b, tt));
        adj[b].PB(MP(a, tt));
    }
    priority_queue<candidate> pq;
    pq.push({0, 0, -1});
    while(!pq.empty()) {
        candidate c = pq.top();
        pq.pop();
        if(vis[c.node]) continue;
        vis[c.node] = 1;
        par[c.node] = c.par;
        if(c.par != -1) children[c.par].PB(c.node);
        dis[c.node] = c.dis;
        for(const pair<int, ll> p : adj[c.node]) if(!vis[p.F])
            pq.push({c.dis + p.S, p.F, c.node});
    }
    cout << solve(0) << endl;
}
