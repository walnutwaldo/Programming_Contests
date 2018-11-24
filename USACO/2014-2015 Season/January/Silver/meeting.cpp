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

#define MAXN 100
#define MAXT 9900

int n, m;
bool vis[MAXN][MAXT + 1][2];
int dis[MAXN][MAXN][2];

void dfs(int node, int t, int c) {
    if(vis[node][t][c]) return;
    vis[node][t][c] = 1;
    F0R(i, n) if(dis[node][i][c] != -1) dfs(i, t + dis[node][i][c], c);
}

int main() {
    ifstream fin("meeting.in");
    ofstream fout("meeting.out");
    fin >> n >> m;
    F0R(i, n) F0R(j, n) F0R(k, 2) dis[i][j][k] = -1;
    F0R(i, m){
        int a, b, c, d;
        fin >> a >> b >> c >> d;
        a--, b--;
        dis[a][b][0] = c;
        dis[a][b][1] = d;
    }
    dfs(0, 0, 0);
    dfs(0, 0, 1);
    F0R(i, MAXT + 1) if(vis[n - 1][i][0] && vis[n - 1][i][1]) {
        fout << i << endl;
        return 0;
    }
    fout << "IMPOSSIBLE" << endl;
}
