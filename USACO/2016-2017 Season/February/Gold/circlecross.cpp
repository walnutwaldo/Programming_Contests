#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (a) - 1; i >= (b); i--)

#define F first
#define S second
#define PB push_back
#define MP make_pair

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct BIT {

    int sz;
    int *tree;

    BIT(int _sz) {
        sz = _sz;
        tree = new int[sz + 1];
        F0R(i, sz + 1) tree[i] = 0;
    }

    void update(int idx, int v) {
        for(idx++; idx <= sz; idx += idx & -idx) tree[idx] += v;
    }

    int query(int idx) {
        int res = 0;
        for(idx++; idx > 0; idx -= idx & -idx) res += tree[idx];
        return res;
    }

    int queryRange(int lo, int hi) { return query(hi) - query(lo - 1); }

};

#define MAXN 50000

int n, firstPos[MAXN];

int main() {
    ifstream fin("circlecross.in");
    ofstream fout("circlecross.out");
    fin >> n;
    BIT bit(2 * n);
    F0R(i, n) firstPos[i] = -1;
    int res = 0;
    F0R(i, 2 * n) {
        int a;
        fin >> a;
        a--;
        if(firstPos[a] == -1) {
            res += bit.query(i);
            firstPos[a] = i;
            bit.update(i, 1);
        } else {
            bit.update(firstPos[a], -1);
            res -= bit.query(firstPos[a]);
        }
    }
    fout << res << endl;
}
