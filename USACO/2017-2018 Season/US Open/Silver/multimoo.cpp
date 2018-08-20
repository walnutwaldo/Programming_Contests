#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

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
#define MAXN 250

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<ull> vul;
typedef complex<ld> point;

int n, singleRes, doubleRes, numCCs, id[MAXN][MAXN], originalID[MAXN * MAXN], sizeOf[MAXN * MAXN];
bool visited[MAXN][MAXN];

unordered_set<int> connections[MAXN * MAXN];

int dfs(int i, int j, int oldID, int newID) {
	if(i < 0 || i >= n || j < 0 || j >= n || id[i][j] != oldID || visited[i][j]) return 0;
	visited[i][j] = 1;
	id[i][j] = newID;
	int res = 1;
	res += dfs(i + 1, j, oldID, newID);
	res += dfs(i - 1, j, oldID, newID);
	res += dfs(i, j + 1, oldID, newID);
	res += dfs(i, j - 1, oldID, newID);
	return res;
}

int dfs2(int node1, int nextColor1) {
	queue<pii> q;
	q.push(MP(node1, nextColor1));
	int res = 0;
	unordered_set<int> seen;
	seen.insert(node1);
	while(!q.empty()) {
		pii p = q.front();
		int node = p.F, nextColor = p.S;
		q.pop();
		res += sizeOf[node];
		vi toRemove;
		for(const int next : connections[node]) if(originalID[next] == nextColor) {
			toRemove.PB(next);
			if(!seen.count(next)) {
				q.push(MP(next, originalID[node]));
				seen.insert(next);
			}
		}
		for(auto it : toRemove) connections[node].erase(it);
	}
	return res;
}

int main() {
	ifstream fin("multimoo.in");
	ofstream fout("multimoo.out");
	fin >> n;
	F0R(i, n) F0R(j, n) fin >> id[i][j];
	F0R(i, n) F0R(j, n) if(!visited[i][j]) {
		originalID[numCCs] = id[i][j];
		sizeOf[numCCs] = dfs(i, j, id[i][j], numCCs);
		singleRes = max(singleRes, sizeOf[numCCs++]);
	}
	F0R(i, n) F0R(j, n - 1) if(id[i][j] != id[i][j + 1]) {
		int id1 = id[i][j], id2 = id[i][j + 1];
		connections[id1].insert(id2);
		connections[id2].insert(id1);
	}
	F0R(i, n - 1) F0R(j, n) if(id[i][j] != id[i + 1][j]) {
		int id1 = id[i][j], id2 = id[i + 1][j];
		connections[id1].insert(id2);
		connections[id2].insert(id1);
	}
	F0R(i, numCCs)
		while(!connections[i].empty()) {
			int c2 = originalID[*(connections[i].begin())];
			doubleRes = max(doubleRes, dfs2(i, c2));
		}
	fout << singleRes << endl << doubleRes << endl;
}
