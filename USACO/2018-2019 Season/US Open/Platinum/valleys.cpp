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

const int dr[8]{0, -1, 0, 1, -1, -1, 1, 1};
const int dc[8]{-1, 0, 1, 0, -1, 1, -1, 1};

struct DSU {
    
    int sz, ct, numComp;
    int **subsize, **holeCnt;
    pii **par;
    
    DSU(int _sz, int _ct) {
    	ct = _ct;
        sz = _sz;
        numComp = 0;
        par = new pii*[sz];
        subsize = new int*[sz];
        holeCnt = new int*[sz];
        F0R(i, sz) {
            par[i] = new pii[sz];
            F0R(j, sz) par[i][j] = MP(-1, -1);
            subsize[i] = new int[sz];
            holeCnt[i] = new int[sz];
        }
    }

    pii root(int r, int c) {
    	if(par[r][c] == MP(r, c)) return MP(r, c);
    	return par[r][c] = root(par[r][c]);
    }

    pii root(pii p) { return root(p.F, p.S); }

    bool exists(int r, int c) {
    	if(r < 0 || r >= sz || c < 0 || c >= sz) return false;
    	return par[r][c] != MP(-1, -1);
    }

    void add(int r, int c) {
    	if(exists(r, c)) return;
        numComp++;
        par[r][c] = MP(r, c);
        subsize[r][c] = 1;
        holeCnt[r][c] = 0;
        F0R(i, ct)
        	if(exists(r + dr[i], c + dc[i]))
        		join(MP(r + dr[i], c + dc[i]), MP(r, c));
    }

    void add(pii p) { add(p.F, p.S); }

    void addHoles(int r, int c, int amt) {
    	pii p = root(r, c);
    	holeCnt[p.F][p.S] += amt;
    }

    int numHoles(int r, int c) {
    	pii p = root(r, c);
    	return holeCnt[p.F][p.S];
    }

    int getSubSize(int r, int c) {
    	pii p = root(r, c);
    	return subsize[p.F][p.S];
    }

    void addHoles(pii p, int amt) { addHoles(p.F, p.S, amt);}

    void join(pii a, pii b) {
    	pii r1 = root(a), r2 = root(b);
    	if(r1 == r2) return;
    	if(subsize[r1.F][r1.S] < subsize[r2.F][r2.S]) swap(r1, r2);
    	par[r2.F][r2.S] = r1;
    	subsize[r1.F][r1.S] += subsize[r2.F][r2.S];
    	holeCnt[r1.F][r1.S] += holeCnt[r2.F][r2.S];
    	numComp--;
    }
    
};

#define MAXN 750

int n;
int numHoles[MAXN * MAXN + 1];
vector<pair<int, pii>> v;

int main() {
    ifstream cin("valleys.in");
    ofstream cout("valleys.out");
    cin >> n;
    F0R(i, n) F0R(j, n) {
        int h;
        cin >> h;
        v.PB(MP(h, MP(i + 1, j + 1)));
    }
    sort(all(v));
    DSU dsu(n + 2, 8);
    F0R(i, n + 2) {
    	dsu.add(0, i);
    	dsu.add(n + 1, i);
    	dsu.add(i, 0);
    	dsu.add(i, n + 1);
    }
    R0F(i, n * n) {
    	dsu.add(v[i].S);
    	numHoles[i] = dsu.numComp;
    }
    numHoles[n * n] = 1;
    dsu = DSU(n + 2, 4);
    ll res = 0;
    F0R(i, n * n) {
    	pii p = v[i].S;
    	dsu.add(p);
    	dsu.addHoles(p, numHoles[i + 1] - numHoles[i]);
    	if(dsu.numHoles(p.F, p.S) == 0)
    		res += dsu.getSubSize(p.F, p.S);
    }
    cout << res << endl;
}
