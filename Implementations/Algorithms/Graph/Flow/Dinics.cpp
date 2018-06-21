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

#define MAXN 5000

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

int n, m, level[MAXN];
bool vis[MAXN];
map<int, ll> adj[MAXN];
vector<pair<int, ll>> lg[MAXN];

bool buildLG(int s, int t) {
	F0R(i, n) lg[i].clear(), vis[i] = level[i] = 0;
	queue<int> q; q.push(s);
	vis[s] = 1;
	while(!q.empty()) {
		int i = q.front(); q.pop();
		for(const pair<int, ll> next : adj[i]) if(!vis[next.F]) {
			vis[next.F] = 1;
			level[next.F] = level[i] + 1;
			q.push(next.F);
		}
	}
	F0R(i, n) for(const pair<int, ll> edge : adj[i]) if(level[edge.F] == 1 + level[i]) lg[i].PB(edge);
	return level[t];
}

ll greedyFlow(int node, int sink, ll flow) {
	if(node == sink) return flow;
	if(!sz(lg[node])) return 0;
	pair<int, ll> next = lg[node].back();
	ll f = greedyFlow(next.F, sink, min(flow, next.S));
	if(f) {
		lg[node].back().S -= f;
		if(!lg[node].back().S) lg[node].pop_back();
		adj[next.F][node] += f;
		adj[node][next.F] -= f;
		if(!adj[node][next.F]) adj[node].erase(next.F);
	} else if(!sz(lg[next.F])) lg[node].pop_back();
	return f;
}

ll dinics(int s, int t) {
	ll flow = 0;
	while(buildLG(s, t)) while(sz(lg[s])) flow += greedyFlow(s, t, ~(1LL << 63));
	return flow;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	F0R(i, m) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		a--, b--;
		if(a == b) continue;
		adj[a][b] += c;
		adj[b][a] += c;
	}
	cout << dinics(0, n - 1) << endl;
}
