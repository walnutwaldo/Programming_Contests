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
#define R real()
#define I image()
#define PI acos(-1)
#define MAXN 100000
#define MAXQ 100000

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;
typedef complex<ld> cld;

struct DSU {

    int *parent, *sizeRooted;

    DSU(int sz) {
        parent = new int[sz], sizeRooted = new int[sz];
        F0R(i, sz) parent[i] = i, sizeRooted[i] = 1;
    }

    int root(int a) {
        if(parent[a] == a) return a;
        return (parent[a] = root(parent[a]));
    }

    void join(int a, int b) {
        int ra = root(a), rb = root(b);
        if(ra == rb) return;
        if(sizeRooted[ra] > sizeRooted[rb]) swap(ra, rb);
        parent[ra] = rb;
        sizeRooted[rb] += sizeRooted[ra];
    }

    bool connected(int a, int b) {
        return root(a) == root(b);
    }

    int componentSize(int a) {
        return sizeRooted[root(a)];
    }

};

int n, q, res[MAXQ];
vector<tuple<int, int, int>> v, queries;
vi connections[MAXN];
DSU dsu(MAXN);

int main() {
    ifstream fin("mootube.in");
    ofstream fout("mootube.out");
    fin >> n >> q;
    F0R(i, n - 1) {
        int a, b, r;
        fin >> a >> b >> r;
        a--, b--;
        v.PB(MT(r, a, b));
    }
    sort(v.rbegin(), v.rend());
    F0R(i, q) {
        int k, v;
        fin >> k >> v;
        v--;
        queries.PB(MT(k, v, i));
    }
    sort(queries.rbegin(), queries.rend());
    int curr = 0;
    for(const tuple<int, int, int> t : queries) {
        int k = get<0>(t);
        while(curr < n - 1 && get<0>(v[curr]) >= k) {
            dsu.join(get<1>(v[curr]), get<2>(v[curr]));
            curr++;
        }
        res[get<2>(t)] = dsu.componentSize(get<1>(t)) - 1;
    }
    F0R(i, q) fout << res[i] << "\n";
    return 0;
}
