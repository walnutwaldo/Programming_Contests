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
#define X real()
#define Y imag()

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ll> point;

int n, m, k;
vector<pii> coords;

struct LazySegmentTree {

    int s, e;
    ll val = 0, lazy = 0;
    LazySegmentTree *lChild = NULL, *rChild = NULL;

    LazySegmentTree(int sz) {
        this->s = 0;
        this->e = sz;
    }

    LazySegmentTree(int s, int e) {
        this->s = s;
        this->e = e;
    }

    void update(int l, int r, ll v) {
        if(l == s && r == e) {
            val += v;
            lazy += v;
            return;
        }
        int mid = (s + e) >> 1;
        if(lazy != 0) {
            if(lChild == NULL) lChild = new LazySegmentTree(s, mid);
            if(rChild == NULL) rChild = new LazySegmentTree(mid, e);
            lChild->val += lazy;
            rChild->val += lazy;
            lChild->lazy += lazy;
            rChild->lazy += lazy;
            lazy = 0;
        }
        if(l < mid) {
            if(lChild == NULL) lChild = new LazySegmentTree(s, mid);
            lChild->update(l, min(r, mid), v);
        }
        if(r > mid) {
            if(rChild == NULL) rChild = new LazySegmentTree(mid, e);
            rChild->update(max(l, mid), r, v);
        }
        if(lChild == NULL) val = min(0LL, rChild->val);
        else if(rChild == NULL) val = min(0LL, lChild->val);
        else val = min(lChild->val, rChild->val);
    }

    ll query(int l, int r) {
        if(l == s && r == e) return val;
        int mid = (s + e) >> 1;
        if(lazy != 0) {
            if(lChild == NULL) lChild = new LazySegmentTree(s, mid);
            if(rChild == NULL) rChild = new LazySegmentTree(mid, e);
            lChild->val += lazy;
            rChild->val += lazy;
            lChild->lazy += lazy;
            rChild->lazy += lazy;
            lazy = 0;
        }
        ll lVal = 0, rVal = 0;
        if(l < mid && lChild != NULL) lVal = lChild->query(l, min(mid, r));
        if(r > mid && rChild != NULL) rVal = rChild->query(max(mid, l), r);
        if(r <= mid) return lVal;
        else if(l >= mid) return rVal;
        else return min(lVal, rVal);
    }
};

pii getBounds(int t) {
    pii res = MP(n, -1);
    set<int> yVals;
    yVals.insert(0);
    yVals.insert(m - 1);
    vector<tuple<int, int, int, int>> toProccess;
    toProccess.PB(MT(0, 0, 0, 0));
    toProccess.PB(MT(n - 1, 0, 0, 0));
    F0R(i, k) {
        int frontEnd = max(0, coords[i].F - t);
        int backEnd = min(n - 1, coords[i].F + t);
        int bottomEnd = max(0, coords[i].S - t);
        int topEnd = min(m - 1, coords[i].S + t);
        yVals.insert(bottomEnd);
        yVals.insert(topEnd);
        if(topEnd < m - 1) yVals.insert(topEnd + 1);
        if(bottomEnd > 0) yVals.insert(bottomEnd - 1);
        toProccess.PB(MT(frontEnd, 1, bottomEnd, topEnd));
        if(frontEnd > 0) toProccess.PB(MT(frontEnd - 1, 0, bottomEnd, topEnd));
        if(backEnd < n - 1) toProccess.PB(MT(backEnd + 1, -1, bottomEnd, topEnd));
    }
    unordered_map<int, int> compY;
    int currCompY = 0;
    for(const int i : yVals) compY[i] = currCompY++;
    LazySegmentTree st(currCompY);
    sort(toProccess.begin(), toProccess.end());
    int i = 0;
    while(i < toProccess.size()) {
        int x = get<0>(toProccess[i]);
        while(i < toProccess.size() && get<0>(toProccess[i]) == x) {
            int change = get<1>(toProccess[i]);
            int loY = compY[get<2>(toProccess[i])];
            int hiY = compY[get<3>(toProccess[i])];
            st.update(loY, hiY + 1, change);
            i++;
        }
        if(st.query(0, currCompY) == 0) {
            res.F = min(res.F, x);
            res.S = max(res.S, x);
        }
    }
    return res;
}

bool works(int t) {
    pii lr = getBounds(t);
    F0R(i, coords.size()) swap(coords[i].F, coords[i].S);
    swap(n, m);
    pii ud = getBounds(t);
    F0R(i, coords.size()) swap(coords[i].F, coords[i].S);
    swap(n, m);
    return (lr.S - lr.F <= 2 * t) && (ud.S - ud.F <= 2 * t);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    F0R(i, k) {
        int x, y;
        cin >> x >> y;
        coords.PB(MP(--x, --y));
    }
    int lo = 0;
    int hi = 1000000000;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(works(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << endl;
    return 0;
}
