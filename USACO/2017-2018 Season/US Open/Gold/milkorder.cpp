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
#define MAXN 100000
#define MAXM 50000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<ull> vul;
typedef complex<ld> point;

int n, m, a[MAXN];
vi res, orderings[MAXM], connections[MAXN];

void setup(int numOrderings) {
	F0R(i, n) connections[i].clear();
	F0R(i, numOrderings)
		F0R(j, orderings[i].size() - 1) 
			connections[orderings[i][j]].PB(orderings[i][j + 1]);
	F0R(i, n) a[i] = 0;
}

bool dfsCycle(int node) {
	if(a[node] != 0) return 2 - a[node];
	a[node] = 1;
	for(auto next : connections[node]) if(dfsCycle(next)) return 1;
	a[node] = 2;
	return 0;
}

bool works(int numOrderings) {
	setup(numOrderings);
	F0R(i, n) if(dfsCycle(i)) return 0;
	return 1;
}

void getOrder(int numOrderings) {
	setup(numOrderings);
	F0R(i, n) for(auto it : connections[i]) a[it]++;
	priority_queue<int, vi, greater<int>> q;
	F0R(i, n) if(!a[i]) q.push(i);
	while(!q.empty()) {
		int curr = q.top();
		q.pop();
		res.PB(curr);
		for(auto next : connections[curr]) if(--a[next] == 0) q.push(next);
	}
}

int main() {
	ifstream fin("milkorder.in");
	ofstream fout("milkorder.out");
	fin >> n >> m;
	F0R(i, m) {
		int cnt;
		fin >> cnt;
		orderings[i] = vi();
		F0R(j, cnt) {
			int a;
			fin >> a;
			orderings[i].PB(a - 1);	
		}
	}
	int lo = 0, hi = m;
	while(lo < hi) {
		int mid = (lo + hi + 1) >> 1;
		if(works(mid)) lo = mid;
		else hi = mid - 1;	
	}
	getOrder(lo);
	F0R(i, n - 1) fout << res[i] + 1 << " ";
	fout << res[n - 1] + 1 << endl;
}
