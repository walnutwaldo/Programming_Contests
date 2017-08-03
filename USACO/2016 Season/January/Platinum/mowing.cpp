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

int n, t;
int numX, numY;
pii points[MAXN];
vector<pii> s[MAXN], e[MAXN];
vector<tuple<int, int, int>> rangesAtX[MAXN];
unordered_map<ll, int> compactX, compactY;
ll answer;

class BIT2 {

public:

    ll *tree;
    ll inBit = 0;
    int l;

    BIT2(ll l) {
        this -> l = l;
        tree = new ll[l + 1];
        memset(tree, 0, (l + 1) * sizeof(ll));
    }

    void update(int ti, int v) {
        for(ti++; ti <= l; ti += (ti & -ti)) tree[ti] += v;
        inBit += v;
    }

    ll querySingle(int idx) {
        if(idx >= l) return inBit;
        idx++;
        ll total = 0;
        for(; idx > 0; idx -= (idx & -idx)) total += tree[idx];
        return total;
    }

    ll queryRange(int lo, int hi) {
        return querySingle(hi) - querySingle(lo - 1);
    }

    ll query(int ti) {
        return inBit - queryRange(ti - t + 1, ti + t - 1);
    }

};

class BIT {

public:

    int l;
    BIT2** tree;

    BIT(int l) {
        this-> l = l;
        tree = new BIT2*[l + 1];
        F0R(i, l + 1) tree[i] = new BIT2(n);
    }

    void update(int idx, int ti, int v) {
        idx++;
        for(; idx <= l; idx += (idx & -idx)) tree[idx]->update(ti, v);
    }

    ll query(int lo, int hi, int ti) {
        return query(hi - 1, ti) - query(lo, ti);
    }

    ll query(int idx, int ti) {
        idx++;
        ll total = 0;
        for(; idx > 0; idx -= (idx & -idx)) total += tree[idx]->query(ti);
        return total;
    }
};

int main() {
    ifstream fin("mowing.in");
    ofstream fout("mowing.out");
    fin >> n >> t;
    vector<ll> xs, ys;
    F0R(i, n) {
        ll x, y;
        fin >> x >> y;
        xs.PB(x);
        ys.PB(y);
        points[i] = MP(x, y);
    }
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    F0R(i, n) {
        if(!compactX.count(xs[i])) compactX[xs[i]] = numX++;
        if(!compactY.count(ys[i])) compactY[ys[i]] = numY++;
    }
    F0R(i, n) {
        ll compX = compactX[points[i].F];
        ll compY = compactY[points[i].S];
    }
    F0R(i, n) points[i] = MP(compactX[points[i].F], compactY[points[i].S]);
    F0R(i, n - 1) {
        if(points[i].S == points[i + 1].S) {
            int x1 = min(points[i].F, points[i + 1].F);
            int x2 = max(points[i].F, points[i + 1].F);
            s[x1].PB(MP(points[i].S, i));
            e[x2].PB(MP(points[i].S, i));
        }
    }
    F0R(i, n - 1) {
        if(points[i].F == points[i + 1].F) {
            int y1 = min(points[i].S, points[i + 1].S);
            int y2 = max(points[i].S, points[i + 1].S);
            rangesAtX[points[i].F].PB(MT(y1, y2, i));
        }
    }
    BIT bit(numY);
    F0R(x, numX) {
        for(const pii i: e[x]) {
            bit.update(i.F, i.S, -1);
        }
        for(const tuple<int, int, int> r: rangesAtX[x]) {
            answer += bit.query(get<0>(r), get<1>(r), get<2>(r));
        }
        for(const pii i: s[x]) {
            bit.update(i.F, i.S, 1);
        }
    }
    fout << answer << "\n";
    return 0;
}
