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
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define MAXN 100000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, k, valLeft[MAXN + 1], valRight[MAXN + 1], ra[MAXN + 1], rb[MAXN + 1], seq[MAXN + 1];
ll totalI, friendlyI;
vector<pii> events[MAXN + 1];

class BIT {

public:

    ll* tree;
    int sz, totalCount;

    BIT(int sz2) {
        sz = sz2;
        tree = new ll[sz + 1];
        memset(tree, 0, sizeof(ll)*(sz + 1));
        totalCount = 0;
    }

    ll query(int idx) {
        ll total = 0;
        for(; idx > 0; idx -= (idx & -idx)) total += tree[idx];
        return total;
    }

    ll update(int idx) {
        totalCount++;
        for(; idx <= sz; idx += (idx & -idx)) tree[idx]++;
    }

};


class ST {

public:
    BIT *bit;
    int *arr, *pleft, *pright;
    ST *lchild, *rchild;
    int l, r;

    ST(int s, int e) {
        l = s;
        r = e;
        arr = new int[r - l + 2];
        arr[0] = 0;
        if(s == e) {
            arr[1] = seq[l];
        } else {
            int m = (l + r)/2;
            lchild = new ST(l, m);
            rchild = new ST(m + 1, r);

            pleft = new int[m - l + 2];
            pright = new int[r - m + 1];
            int i = 1;
            int j = 1;
            int ij = 1;
            while(ij < r - l + 2) {
                if(j == r - m + 1 || (i < m - l + 2 && lchild->arr[i] < rchild->arr[j])) {
                    pleft[i] = ij;
                    arr[ij++] = lchild->arr[i++];
                } else {
                    pright[j] = ij;
                    arr[ij++] = rchild->arr[j++];
                }
            }
        }
        bit = new BIT(r - l + 2);
    }

    int update(int p) {
        if(l == p && r == p) {
            bit->update(1);
            return 1;
        }
        int mid = (l + r) / 2;
        int apos = -1;
        if(mid >= p) apos = pleft[lchild->update(p)];
        else apos = pright[rchild->update(p)];
        bit->update(apos);
        return apos;
    }

    ll query(int lo, int hi, int v) {
        if(lo == l && hi == r) {
            int i = UB(arr, arr + hi - lo + 2, v) - arr;
            return bit->totalCount - bit->query(i - 1);
        }
        int mid = (l + r) / 2;
        if(hi <= mid) {
            return lchild->query(lo, hi, v);
        } else if(lo > mid) {
            return rchild->query(lo, hi, v);
        } else {
            return lchild->query(lo, mid, v) + rchild->query(mid + 1, hi, v);
        }
    }
};

void countTotal() {
    BIT x(n);
    FOR(i, 1, n + 1) {
        totalI += x.totalCount - x.query(seq[i]);
        x.update(seq[i]);
    }
}

void addEvents() {
    FOR(i, 1, n + 1) {
        events[min(i + k, n)].PB(MP(i, 1));
        events[max(i - k - 1, 0)].PB(MP(i, -1));
    }
}

void countFriendly() {
    addEvents();
    ST root(1, n);
    FOR(i, 1, n + 1) {
        root.update(ra[i]);
        F0R(j, events[i].size()) {
            friendlyI += events[i][j].second * root.query(1, ra[events[i][j].first], rb[events[i][j].first]);
        }
    }
}

int main() {
    ifstream fin("friendcross.in");
    ofstream fout("friendcross.out");
    fin >> n >> k;
    FOR(i, 1, n + 1) fin >> valLeft[i];
    FOR(i, 1, n + 1) fin >> valRight[i];
    FOR(i, 1, n + 1) ra[valLeft[i]] = i;
    FOR(i, 1, n + 1) rb[valRight[i]] = i;
    FOR(i, 1, n + 1) seq[ra[i]] = rb[i];
    countTotal();
    countFriendly();
    fout << totalI - friendlyI;
    return 0;
}
