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
#define MAXN 35000
#define MAXK 50

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, k;
int dp[MAXN + 1][MAXK + 1];
int cake[MAXN], lastApperenceOf[MAXN], lastSame[MAXN];

struct ST {

    int l;
    int *a, *lazy;

    ST(int length) {
        this->l = exp2(ceil(log2(length)));
        a = new int[2 * l];
        lazy = new int[2 * l];
        F0R(i, 2 * l) {
            a[i] = 0;
            lazy[i] = 0;
        }
    }

    void update(int lo, int hi, int node, int s, int e, int val) {
        if(lo >= hi) return;
        if(lo == s && hi == e) {
            a[node] += val;
            lazy[node] += val;
            return;
        }
        a[2 * node] += lazy[node];
        lazy[2 * node] += lazy[node];
        a[2 * node + 1] += lazy[node];
        lazy[2 * node + 1] += lazy[node];
        lazy[node] = 0;
        int mid = (s + e) >> 1;
        if(lo < mid) update(lo, min(mid, hi), node * 2, s, mid, val);
        if(hi > mid) update(max(lo, mid), hi, node * 2 + 1, mid, e, val);
        a[node] = max(a[2 * node], a[2 * node + 1]);
    }

    void update(int lo, int hi, int val) {
        update(lo, hi, 1, 0, l, val);
    }

    int maxInRange(int lo, int hi, int node, int s, int e) {
        if(lo >= hi) return 0;
        if(lo == s && hi == e) return a[node];
        a[2 * node] += lazy[node];
        lazy[2 * node] += lazy[node];
        a[2 * node + 1] += lazy[node];
        lazy[2 * node + 1] += lazy[node];
        lazy[node] = 0;

        int mid = (s + e) >> 1;
        int res = 0;
        int m1 = maxInRange(lo, min(hi, mid), 2 * node, s, mid);
        int m2 = maxInRange(max(lo, mid), hi, 2 * node + 1, mid, e);
        return max(m1, m2);
    }

    int maxInRange(int lo, int hi) {
        return maxInRange(lo, hi, 1, 0, l);
    }

    void print() {
        F0R(i, 2 * l) cout << a[i] << " ";
        cout << endl;
    }

};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    F0R(i, n) lastApperenceOf[i] = -1;
    F0R(i, n) {
        cin >> cake[i];
        cake[i]--;
        lastSame[i] = lastApperenceOf[cake[i]];
        lastApperenceOf[cake[i]] = i;
    }
    FOR(boxes, 1, k + 1) {
        ST st(n + 1);
        F0R(i, n + 1) {
            st.update(i, i + 1, dp[i][boxes - 1]);
        }
        FOR(i, 1, n + 1) {
            st.update(lastSame[i - 1] + 1, i, 1);
            dp[i][boxes] = st.maxInRange(0, i);
        }
    }
    cout << dp[n][k] << "\n";
    return 0;
}
