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

#define CITIES 1000

pll edge[CITIES][CITIES];
pll dis[CITIES];
bool vis[CITIES];
int a, b, n;

pll better(pll x, pll y) {
    if (x.F == -1) return y;
    else if (y.F == -1) return x;
    if (x < y) return x;
    return y;
}

pll operator +(const pll &x, const pll &y) {
    return MP(x.F + y.F, x.S + y.S);
}

int main() {
    ifstream fin("cowroute.in");
    ofstream fout("cowroute.out");
    F0R(i, CITIES) dis[i] = MP(-1, -1);
    F0R(i, CITIES) F0R(j, CITIES) edge[i][j] = MP(-1, -1);
    fin >> a >> b >> n;
    a--, b--;
    F0R(i, n) {
        ll c;
        int numCities;
        fin >> c >> numCities;
        vi v;
        F0R(j, numCities) {
            int x;
            fin >> x;
            v.PB(x - 1);
        }
        F0R(j, numCities) FOR(k, j + 1, numCities) edge[v[j]][v[k]] = better(edge[v[j]][v[k]], MP(c, k - j));
    }
    dis[a] = MP(0, 0);
    priority_queue<pair<pll, int>, vector<pair<pll, int>>, greater<pair<pll,int>>> pq;
    pq.push(MP(dis[a], a));
    while(!pq.empty()) {
        pair<pll, int> p = pq.top(); pq.pop();
        if(vis[p.S]) continue;
        dis[p.S] = p.F;
        vis[p.S] = 1;
        F0R(i, CITIES) if(edge[p.S][i].F != -1) pq.push(MP(p.F + edge[p.S][i], i));
    }
    fout << dis[b].F << " " << dis[b].S << endl;
}
