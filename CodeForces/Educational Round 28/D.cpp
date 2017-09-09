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
#define MAXN 500

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n, m, k, q;
vector<tuple<ll, int, int>> points;

bool works(int numP) {
    if(numP == q + 1) return true;
    int dp[n][m];
    memset(dp, 0, sizeof dp);
    F0R(i, numP) {
        int a = get<1>(points[i]), b = get<2>(points[i]);
        dp[a][b]++;
    }
    F0R(a, n) F0R(b, m) {
        if(a > 0) dp[a][b] += dp[a - 1][b];
        if(b > 0) dp[a][b] += dp[a][b - 1];
        if(a > 0 && b > 0) dp[a][b] -= dp[a - 1][b - 1];
    }
    FOR(a, k - 1, n) FOR(b, k - 1, m) {
        int total = dp[a][b];
        if(a > k - 1) total -= dp[a - k][b];
        if(b > k - 1) total -= dp[a][b - k];
        if(a > k - 1 && b > k - 1) total += dp[a - k][b - k];
        if(total == k * k) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k >> q;
    F0R(i, q) {
        int a, b, t;
        cin >> a >> b >> t;
        a--, b--;
        points.PB(MT(t, a, b));
    }
    sort(points.begin(), points.end());
    int lo = 1;
    int hi = q + 1;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(works(mid)) hi = mid;
        else lo = mid + 1;
    }
    if(lo == q + 1) cout << "-1\n";
    else cout << get<0>(points[lo - 1]) << "\n";
    return 0;
}
