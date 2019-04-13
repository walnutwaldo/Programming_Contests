#include "grader.h"

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

#define MAXN 100000

int par[MAXN][17], dep[MAXN], s[MAXN];
pii loc[MAXN];
vi adj[MAXN];

void addRoad(int a, int b){
	adj[a].PB(b);
	adj[b].PB(a);
}

void dfs(int node) {
	FOR(i, 1, 17) par[node][i] = par[par[node][i - 1]][i - 1];
	s[node] = 1;
	for(const int next : adj[node]) if(next != par[node][0]) {
		par[next][0] = node;
		dep[next] = dep[node] + 1;
		dfs(next);
		s[node] += s[next];
	}
}

int raise(int node, int amt) {
	for(int i = 0; i < 17; i++, amt >>= 1) if(amt & 1)
		node = par[node][i];
	return node;
}

int lca(int a, int b) {
	if(dep[a] < dep[b]) b = raise(b, dep[b] - dep[a]);
	else a = raise(a, dep[a] - dep[b]);
	if(a == b) return a;
	R0F(i, 17) if(par[a][i] != par[b][i]) {
		a = par[a][i];
		b = par[b][i];
	}
	return par[a][0];
}

void dfsBuild(int node, int x, int y) {
	setFarmLocation(node, x, y);
	loc[node] = MP(x, y);
	int runningX = x, runningY = y + s[node];
	for(const int next : adj[node]) if(next != par[node][0]) {
		runningY -= s[next];
		dfsBuild(next, runningX + 1, runningY);
		runningX += s[next];
	}
}

void buildFarms() {
	dfs(0);
	dfsBuild(0, 1, 1);
}

void notifyFJ(int a, int b){
	int l = lca(a, b);
	if(l == a) addBox(loc[a].F, loc[a].S, loc[b].F, loc[b].S);
	else if(l == b) addBox(loc[b].F, loc[b].S, loc[a].F, loc[a].S);
	else {
		addBox(loc[l].F, loc[l].S, loc[a].F, loc[a].S);
		l = raise(b, dep[b] - dep[l] - 1);
		addBox(loc[l].F, loc[l].S, loc[b].F, loc[b].S);
	}
}
