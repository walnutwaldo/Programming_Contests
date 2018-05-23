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

struct BIT {

	int sz;
	ll* tree;

	BIT(int sz) {
		this->sz = sz;
		tree = new ll[sz + 1];
		memset(tree, 0, (sz + 1) * sizeof(ll));
	}

	void update(int idx, ll v) {
		for(idx++; idx <= sz; idx += idx & -idx)
			tree[idx] += v;
	}

	ll query(int idx) {
		ll res = 0;
		for(idx++; idx > 0; idx -= idx & -idx)
			res += tree[idx];
        return res;
	}

	ll queryRange(int lo, int hi) {
		return query(hi) - query(lo - 1);
	}

};

int n;
ll res;
vector<pii> v;

int main() {
	ifstream fin("sort.in");
	ofstream fout("sort.out");
	fin >> n;
	if(n == 1) {
        fout << 0 << "\n";
        return 0;
	}
	F0R(i, n) {
		int a;
		fin >> a;
		v.PB(MP(a, i));
	}
	sort(v.begin(), v.end());
	BIT x(n);
	int last = 0;
	for(const pii p : v) {
        last = max(last, p.S);
        ll contrib = p.S - x.query(p.S);
        if(last > p.S) contrib += last - p.S - x.queryRange(p.S, last - 1);
        res += max(1LL, contrib);
        x.update(p.S, 1);
	}
	fout << res << "\n";
}
