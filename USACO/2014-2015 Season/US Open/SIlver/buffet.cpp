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

#define MAXN 1000

int n, e, dis[MAXN][MAXN], dp[MAXN];
vi adj[MAXN];
vector<pii> qv;

void bfs() {
    F0R(i, n) F0R(j, n) dis[i][j] = -1;
    queue<tuple<int, int, int>> q;
    F0R(i, n) q.push(MT(i, i, 0)), dis[i][i] = 0;
    while(!q.empty()) {
        tuple<int, int, int> t = q.front();
        q.pop();
        int strt = get<0>(t), node = get<1>(t), d = get<2>(t);
        for(const int next : adj[node]) if(dis[strt][next] == -1) {
            dis[strt][next] = d + 1;
            q.push(MT(strt, next, d + 1));
        }
    }
}

int main() {
	ifstream fin("buffet.in");
	ofstream fout("buffet.out");
    fin >> n >> e;
    F0R(i, n) {
        int d, q;
        fin >> q >> d;
        qv.PB(MP(q, i));
        F0R(j, d) {
                int x;
                fin >> x;
                adj[i].PB(x - 1);
        }
    }
    bfs();
    sort(all(qv));
    int res = 0;
    R0F(i, n) {
        FOR(j, i + 1, n) if(dis[qv[i].S][qv[j].S] != -1) dp[i] = max(dp[i], dp[j] - e * dis[qv[i].S][qv[j].S]);
        dp[i] += qv[i].F;
        res = max(res, dp[i]);
    }
    fout << res << endl;
}
