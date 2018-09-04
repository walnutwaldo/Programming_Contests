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

int n, m, numComp, comp[MAXN], compSize[MAXN + 1], onPath[MAXN + 1][2];
bool vis[MAXN];
vi topo, adj[MAXN][2];
set<int> adjComp[MAXN + 1][2];

void calcPath(int dir) {
    onPath[comp[0]][dir] = compSize[comp[0]];
    if(dir == 1) reverse(all(topo));
    F0R(i, n) if(onPath[comp[topo[i]]][dir] && (i == 0 || comp[topo[i]] != comp[topo[i - 1]]))
        for(auto next : adjComp[comp[topo[i]]][dir]) onPath[next][dir] = max(onPath[next][dir], onPath[comp[topo[i]]][dir] + compSize[next]);
}

void dfsSCC(int node, int c) {
    if(comp[node]) return;
    comp[node] = c;
    compSize[c]++;
    for(auto next : adj[node][1]) dfsSCC(next, c);
}

void dfs(int node) {
    if(vis[node]) return;
    vis[node] = 1;
    for(auto next : adj[node][0]) dfs(next);
    topo.PB(node);
}

int main() {
    ifstream fin("grass.in");
    ofstream fout("grass.out");
    fin >> n >> m;
    F0R(i, m) {
        int u, v;
        fin >> u >> v;
        u--, v--;
        adj[u][0].PB(v);
        adj[v][1].PB(u);
    }
    F0R(i, n) dfs(i);
    reverse(all(topo));
    F0R(i, n) if(!comp[topo[i]]) dfsSCC(topo[i], ++numComp);
    F0R(i, n) F0R(j, 2) for(auto next : adj[i][j]) if(comp[i] != comp[next]) adjComp[comp[i]][j].insert(comp[next]);
    F0R(j, 2) calcPath(j);
    int res = compSize[comp[0]];
    FOR(i, 1, numComp + 1) if(onPath[i][1]) for(auto next : adjComp[i][0]) if(onPath[next][0]) res = max(res, onPath[i][1] + onPath[next][0] - compSize[comp[0]]);
    fout << res << endl;
}
