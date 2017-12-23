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

struct LazySegmentTree {

    int sz;
    ll *tree, *lazy;

    LazySegmentTree(int pre_sz) {
        sz = 1 << (int)ceil(log2(pre_sz));
        tree = new ll[2 * sz];
        lazy = new ll[2 * sz];
        memset(tree, 0, 2 * sz * sizeof(ll));
        memset(lazy, 0, 2 * sz * sizeof(ll));
        F0R(i, pre_sz) update(i, i + 1, i + 1);
    }

    void propogateLazy(int idx) {
        tree[2 * idx] += lazy[idx];
        tree[2 * idx + 1] += lazy[idx];
        lazy[2 * idx] += lazy[idx];
        lazy[2 * idx + 1] += lazy[idx];
        lazy[idx] = 0;
    }

    void update(int idx, int s, int e, int l, int r, ll v) {
        if(l == s && r == e) {
            tree[idx] += v;
            lazy[idx] += v;
            return;
        }
        propogateLazy(idx);
        int mid = (s + e) >> 1;
        if(l < mid) update(2 * idx, s, mid, l, min(r, mid), v);
        if(r > mid) update(2 * idx + 1, mid, e, max(l, mid), r, v);
        tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
    }

    void update(int l, int r, ll v) {
        if(l >= r) return;
        update(1, 0, sz, l, r, v);
    }

    ll query(int idx, int s, int e, int l, int r) {
        if(l == s && r == e) return tree[idx];
        propogateLazy(idx);
        int mid = (s + e) >> 1;
        if(l < mid && r > mid) return max(query(2 * idx, s, mid, l, min(mid, r)), query(2 * idx + 1, mid, e, max(mid, l), r));
        else if(l < mid) return query(2 * idx, s, mid, l, min(mid, r));
        else return query(2 * idx + 1, mid, e, max(mid, l), r);
    }

    ll query(int l, int r) {
        if(r <= l) return -1;
        return query(1, 0, sz, l, r);
    }
};

int n, c[MAXN];

int main() {
    ifstream fin("greedy.in");
    ofstream fout("greedy.out");
    fin >> n;
    F0R(i, n) fin >> c[i];
    LazySegmentTree st(n - 1);
    F0R(i, n) {
        if(st.query(n - 1 - i, n - 1) >= n - i) {
            fout << n - i << endl;
            return 0;
        }
        st.update(c[i], n - 1, -1);
    }
    fout << 0 << endl;
    return 0;
}
