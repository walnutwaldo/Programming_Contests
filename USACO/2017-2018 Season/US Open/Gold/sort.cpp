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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<ull> vul;
typedef complex<ld> point;

struct BIT{
	
	int SZ;
	int *tree;

	BIT(int sz) {
		SZ = sz;
		tree = new int[sz + 1];
		memset(tree, 0, (sz + 1) * sizeof(int));
	}

	void update(int idx) { for(idx++; idx <= SZ; idx += idx & -idx) tree[idx]++; }

	int query(int idx) {
		int res = 0;
		for(idx++; idx > 0; idx -= idx & -idx) res += tree[idx];
		return res;
	}

};

int n, res;
pii a[MAXN];

int main() {
	ifstream fin("sort.in");
	ofstream fout("sort.out");
	fin >> n;
	F0R(i, n) {
		fin >> a[i].F;
		a[i].S = i;
	}
	sort(a, a + n);
	BIT x(n);
	R0F(i, n - 1) {
		x.update(a[i + 1].S);
		res = max(res, x.query(i));
	}
	fout << max(1, res) << endl;
}
