#include <bits/stdc++.h>

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

#define PI acos(-1)

#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define SQ(x) ((x) * (x))

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef vector<ll> vll;
typedef vector<ull> vul;
typedef complex<ld> point;
typedef complex<ld> cld;
typedef vector<cld> vcld;

struct segTree{

    bool *tree, *lazy;
    int n;

    segTree(int sz = 1){
        n = 1 << (32 - __builtin_clz(sz - 1));
        tree = new bool[2 * n];
        memset(tree, 0, sizeof(bool) * 2 * n);
        lazy = new bool[2 * n];
        memset(lazy, 0, sizeof(bool) * 2 * n);
    }

    void propLazy(int node) {
        if(lazy[node]) F0R(i, 2) {
            if(!tree[2 * node + i]) lazy[2 * node + i] = 1;
            tree[2 * node + i] = 1;
        }
    }

    void pullChildren(int node) {
        tree[node] = tree[2 * node] && tree[2 * node + 1];
    }

    void turnOn(int lo, int hi, int node = 1, int s = 0, int e = -1) {
        if(e == -1) e = n;
        if(e <= lo || s >= hi) return;
        if(s >= lo && e <= hi) {
            if(!tree[node]) lazy[node] = 1;
            tree[node] = 1;
            return;
        }
        propLazy(node);
        turnOn(lo, hi, 2 * node, s, (s + e) >> 1);
        turnOn(lo, hi, 2 * node + 1, (s + e) >> 1, e);
        pullChildren(node);
    }

    bool allOn(int lo, int hi, int node = 1, int s = 0, int e = -1) {
        if(e == -1) e = n;
        if(e <= lo || s >= hi) return 1;
        if(lo <= s && e <= hi) return tree[node];
        propLazy(node);
        return allOn(lo, hi, 2 * node, s, (s + e) >> 1) && allOn(lo, hi, 2 * node + 1, (s + e) >> 1, e);
    }

};

struct cow{

    ll x, y, r;

    cow(ll xx, ll yy, ll rr) {
        x = xx;
        y = yy;
        r = rr;
    }

    bool operator < (const cow& c) const {
        return y < c.y;
    }

};

int n, res;
vector<cow> cows;
set<ll> points;
map<ll, int> compIdx;

int main() {
    ifstream fin("stampede.in");
    ofstream fout("stampede.out");
    fin >> n;
    F0R(i, n) {
        ll x, y, r;
        fin >> x >> y >> r;
        cows.PB(cow(x, y, r));
        points.insert(-x * r);
        points.insert(-(x + 1) * r);
    }
    int curr = 0;
    for(const ll l : points) compIdx[l] = curr++;
    sort(all(cows));
    segTree st(sz(points) - 1);
    F0R(i, n) {
        int lo = compIdx[-(cows[i].x + 1) * cows[i].r];
        int hi = compIdx[-cows[i].x * cows[i].r];
        if(!st.allOn(lo, hi)) res++;
        st.turnOn(lo, hi);
    }
    fout << res << endl;
}
