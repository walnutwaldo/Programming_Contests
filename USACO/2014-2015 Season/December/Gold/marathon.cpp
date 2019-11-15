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

struct BIT {

    int sz;
    ll *tree;

    BIT(int _sz) {
        sz = _sz;
        tree = new ll[sz + 1];
        F0R(i, sz + 1) tree[i] = 0;
    }

    void update(int idx, ll v) { for(int i = idx + 1; i <= sz; i += i & -i) tree[i] += v; }

    ll query(int idx) {
        ll res = 0;
        for(int i = idx + 1; i; i -= i & -i) res += tree[i];
        return res;
    }

    ll query(int lo, int hi) { return query(hi) - query(lo - 1); }

};

struct ST {

    int sz;
    ll *tree;

    ST(int _sz) {
        sz = 1 << (32 - __builtin_clz(_sz - 1));
        tree = new ll[sz << 1];
        F0R(i, sz << 1) tree[i] = 0;
    }

    void update(int idx, ll v) {
        idx += sz;
        tree[idx] = v;
        for(idx /= 2; idx > 0; idx /= 2) tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
    }

    ll query(int lo, int hi) {
        lo += sz, hi += sz;
        ll res = tree[lo];
        while(lo <= hi) {
            if(lo % 2 == 1) res = min(res, tree[lo++]);
            if(hi % 2 == 0) res = min(res, tree[hi--]);
            lo >>= 1, hi >>= 1;
        }
        return res;
    }

};

#define MAXN 100000

int n, q;
pll loc[MAXN];

ll dis(pll p1, pll p2) { return abs(p2.F - p1.F) + abs(p2.S - p1.S); }

int main() {
    ifstream cin("marathon.in");
    ofstream cout("marathon.out");
    cin >> n >> q;
    F0R(i, n) cin >> loc[i].F >> loc[i].S;
    BIT bit(n - 1);
    ST st(n - 2);
    F0R(i, n - 1) bit.update(i, dis(loc[i], loc[i + 1]));
    F0R(i, n - 2) st.update(i, dis(loc[i], loc[i + 2]) - dis(loc[i], loc[i + 1]) - dis(loc[i + 1], loc[i + 2]));
    F0R(i, q) {
        char c;
        cin >> c;
        if(c == 'Q') {
            int lo, hi;
            cin >> lo >> hi;
            lo--, hi--;
            ll ret = bit.query(lo, hi - 1);
            if(hi - 2 >= lo) ret += st.query(lo, hi - 2);
            cout << ret << "\n";
        } else {
            int idx;
            ll x, y;
            cin >> idx >> x >> y;
            idx--;
            if(idx) bit.update(idx - 1, dis(MP(x, y), loc[idx - 1]) - dis(loc[idx], loc[idx - 1]));
            if(idx < n - 1) bit.update(idx, dis(MP(x, y), loc[idx + 1]) - dis(loc[idx], loc[idx + 1]));

            loc[idx] = MP(x, y);
            if(idx > 1) st.update(idx - 2, dis(loc[idx], loc[idx - 2]) - dis(loc[idx], loc[idx - 1]) - dis(loc[idx - 1], loc[idx - 2]));
            if(idx > 0 && idx < n - 1) st.update(idx - 1, dis(loc[idx - 1], loc[idx + 1]) - dis(loc[idx], loc[idx + 1]) - dis(loc[idx - 1], loc[idx]));
            if(idx < n - 2) st.update(idx, dis(loc[idx], loc[idx + 2]) - dis(loc[idx], loc[idx + 1]) - dis(loc[idx + 1], loc[idx + 2]));
        }
    }
}
