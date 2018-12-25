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

int n, m, dep[MAXN], par[MAXN][17], add[MAXN], edgeLeft[MAXN], holdLeft[MAXN], holdInit[MAXN];
bool pos[MAXN], placed[MAXN];
vi adj[MAXN], freeing[MAXN];

void dfs(int node) {
    FOR(i, 1, 17) par[node][i] = par[par[node][i - 1]][i - 1];
    for(const int next : adj[node]) if(next != par[node][0]) {
        dep[next] = dep[node] + 1;
        par[next][0] = node;
        dfs(next);
    }
}

int getAnc(int node, int d) {
    R0F(i, 17) if(dep[node] - (1 << i) >= d) {
        node = par[node][i];
    }
    return node;
}

void solve(int node, int running) {
    running += add[node];
    if(running == 0) pos[node] = 1;
    for(const int next : adj[node]) if(next != par[node][0]) solve(next, running);
}

bool possible() {
    vi toProcess;
    F0R(i, n) {
        edgeLeft[i] = sz(adj[i]);
        holdLeft[i] = holdInit[i];
        if(edgeLeft[i] <= 1 && holdLeft[i] == 0) {
            toProcess.PB(i);
            placed[i] = 1;
        }
    }
    F0R(i, sz(toProcess)) {
        int node = toProcess[i];
        for(const int next : adj[node]) if(!placed[next] && --edgeLeft[next] <= 1 && holdLeft[next] == 0) {
            toProcess.PB(next);
            placed[next] = 1;
        }
        for(const int next : freeing[node]) if(--holdLeft[next] == 0 && edgeLeft[next] <= 1) {
            toProcess.PB(next);
            placed[next] = 1;
        }
    }
    return sz(toProcess) == n;
}

int main() {
    ifstream fin("gathering.in");
    ofstream fout("gathering.out");
    fin >> n >> m;
    F0R(i, n - 1) {
        int x, y;
        fin >> x >> y;
        x--, y--;
        adj[x].PB(y);
        adj[y].PB(x);
    }
    dfs(0);
    F0R(i, m) {
        int a, b;
        fin >> a >> b;
        a--, b--;
        holdInit[b]++;
        freeing[a].PB(b);
        if(dep[a] < dep[b] && a == getAnc(b, dep[a])) {
            add[0]++;
            add[getAnc(b, dep[a] + 1)]--;
        } else {
            add[a]++;
        }
    }
    solve(0, 0);
    if(!possible()) F0R(i, n) pos[i] = 0;
    F0R(i, n) fout << pos[i] << "\n";
}
