#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define MAXN 100000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct RMQ {

    int n;
    ll* arr;
    vector<vi> sparse;

    RMQ(int sz) {
        n = sz;
        arr = new ll[n];
        memset(arr, 0, n * sizeof(ll));
    }

    void update(int i, ll v) {
        arr[i] += v;
    }

    void genRMQ() {
        F0R(i, n) sparse.PB(vi());
        F0R(i, n) sparse[i].PB(arr[i]);
        FOR(i, 1, log2(n)) F0R(j, n) {
            if(j + (1 << i) > n) sparse[j].PB(sparse[j][i - 1]);
            else sparse[j].PB(max(sparse[j][i - 1], sparse[j + (1 << (i - 1))][i - 1]));
        }
    }

    ll query(int l, int r) {
        int s = (int)ceil(log2(r - l + 1)) - 1;
        return max(sparse[l][s], sparse[r + 1 - (1 << s)][s]);
    }
};

int n;
ll m, f[MAXN];
RMQ rmq(MAXN);

int main() {
    ifstream fin("hayfeast.in");
    ofstream fout("hayfeast.out");
    fin >> n >> m;
    F0R(i, n) {
        ll s;
        fin >> f[i] >> s;
        rmq.update(i, s);
    }
    rmq.genRMQ();
    FOR(i, 1, n) f[i] += f[i - 1];
    ll res = 1000000000000000LL;
    ll baseF = 0;
    F0R(i, n) {
        int j = LB(f, f + n, baseF + m) - f;
        if(j < n) res = min(rmq.query(i, j), res);
        baseF = f[i];
    }
    fout << res << "\n";
    return 0;
}
