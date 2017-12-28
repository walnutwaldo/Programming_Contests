// Uses Divide and Conquer
// Faster than the other solution
// Is O(N^2*KlogN)
#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define rand31() ((rand() << 16) | (rand() << 1) | (rand() & 1))
#define rand32() ((rand() << 17) | (rand() << 2) | (rand() & 3))
#define rand63() (((ll)rand() << 48) | ((ll)rand() << 33) | ((ll)rand() << 18) | ((ll)rand() << 3) | ((ll)rand() & 7))
#define rand64() (((ll)rand() << 49) | ((ll)rand() << 34) | ((ll)rand() << 19) | ((ll)rand() << 4) | ((ll)rand() & 15))

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define MAXN 1000
#define MAXK 7

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, k;
ll r[MAXN], ps[MAXN + 1];
pair<ll, int> dp[MAXK][MAXN];
bool solved[MAXN];

void solveDP(int d, int lo, int hi, int s, int e) {
    if(hi <= lo) return;
    int mid = (lo + hi) >> 1;
    dp[d][mid] = MP(1e15, -1);
    FOR(i, s, min(mid + 1, e)) dp[d][mid] = min(dp[d][mid], MP(dp[d - 1][i - 1].F + dp[0][mid].F - dp[0][i - 1].F - i * (ps[mid] - ps[i - 1]), i));
    solveDP(d, lo, mid, s, dp[d][mid].S + 1);
    solveDP(d, mid + 1, hi, dp[d][mid].S, e);
}

ll solveLinear() {
    dp[0][0] = MP(0, 0);
    FOR(i, 1, n) dp[0][i] = MP(dp[0][i - 1].F + r[i] * i, 0);
    ps[0] = r[0];
    FOR(i, 1, n) ps[i] = r[i] + ps[i - 1];
    FOR(d, 1, k) solveDP(d, d, n, d, n);
    return dp[k - 1][n - 1].F;
}

void rot() {
    ll temp = r[0];
    F0R(i, n) r[i] = r[i + 1];
    r[n - 1] = temp;
}

int main() {
    ifstream fin("cbarn.in");
    ofstream fout("cbarn.out");
    fin >> n >> k;
    F0R(i, n) fin >> r[i];
    ll res = 1e15;
    F0R(i, n) {
        res = min(res, solveLinear());
        rot();
    }
    fout << res << "\n";
    return 0;
}
