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

#define INF 1e15
#define MAXN 50000

int n, m, k;
ll dis[MAXN], dis2[MAXN];
vector<pair<int, ll>> adj[MAXN];

void dijkstra(ll* d, priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>>& pq) {
    while(!pq.empty()) {
        pair<ll, int> p = pq.top(); pq.pop();
        if(d[p.S] != -INF) continue;
        d[p.S] = p.F;
        for(const pair<int, ll> next : adj[p.S]) if(d[next.F] == -INF) pq.push(MP(d[p.S] + next.S, next.F));
    }
}

int main() {
    ifstream fin("dining.in");
    ofstream fout("dining.out");

    fin >> n >> m >> k;
    F0R(i, m) {
        int a, b;
        ll t;
        fin >> a >> b >> t;
        a--, b--;
        adj[a].PB(MP(b, t));
        adj[b].PB(MP(a, t));
    }

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    F0R(i, n) dis[i] = -INF;
    pq.push(MP(0, n - 1));
    dijkstra(dis, pq);

    F0R(i, n) dis2[i] = -INF;
    F0R(i, k) {
        int node;
        ll y;
        fin >> node >> y;
        node--;
        pq.push(MP(dis[node] - y, node));
    }
    dijkstra(dis2, pq);

    F0R(i, n - 1)
        if(dis[i] >= dis2[i]) fout << "1\n";
        else fout << "0\n";
}
