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
#define MAXN 1000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, k;
ll tree[MAXN + 1], r[MAXN], total;

ll update(int idx, ll v) {
    idx++;
    for(; idx <= n; idx += (idx & -idx)) tree[idx] += v;
    total += v;
}

ll query(int idx) {
    ll v = 0;
    for(; idx > 0; idx -= (idx & -idx)) v += tree[idx];
    return v;
}

ll sum(int lo, int hi) {
    if(hi < lo) {
        if(hi == lo - 1) return total;
        return total - sum(hi + 1, lo - 1);
    }
    return query(hi + 1) - query(lo);
}

int main() {
    ifstream fin("cbarn.in");
    ofstream fout("cbarn.out");
    fin >> n >> k;
    F0R(i, n) {
        ll v;
        fin >> v;
        update(i, v);
        r[i] = v;
    }
    ll minCost = -1;
    F0R(s, n) {
        ll dp[n][k + 1];
        F0R(i, n) F0R(j, k) dp[i][j] = -1;
        dp[0][0] = 0;
        F0R(l, n) {
            dp[0][0] += (ll)l * r[(s + l) % n];
        }
        if(dp[0][0] < minCost || minCost == -1) minCost = dp[0][0];
        F0R(l, n) FOR(j, 1, k) {
            ll m  = -1;
            F0R(last, l) {
                if(dp[last][j - 1] != -1) {
                    ll cost = dp[last][j - 1];
                    cost -= (l - last) * sum((s + l) % n, (s + n - 1) % n);
                    if(m == -1 || cost < m) m = cost;
                }
            }
            dp[l][j] = m;
            if(dp[l][j] != -1 && (dp[l][j] < minCost || minCost == -1)) minCost = dp[l][j];
        }
    }
    fout << minCost << "\n";
    return 0;
}
