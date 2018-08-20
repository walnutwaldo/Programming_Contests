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
#define MAXN 100

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, k;
ll r[MAXN];
int main() {
    ifstream fin("cbarn2.in");
    ofstream fout("cbarn2.out");
    fin >> n >> k;
    F0R(i, n) fin >> r[i];
    ll minCost = -1;
    F0R(s, n) {
        ll dp[n][k + 1];
        F0R(i, n) F0R(j, k) dp[i][j] = -1;
        dp[0][0] = 0;
        F0R(l, n) {
            dp[0][0] += (ll)l * r[(s + l) % n];
        }
        F0R(l, n) FOR(j, 1, k) {
            ll m  = -1;
            F0R(last, l) {
                if(dp[last][j - 1] != -1) {
                    ll cost = dp[last][j - 1];
                    FOR(l2, l, n) cost -= (l - last) * r[(s + l2) % n];
                    if(m == -1 || cost < m) m = cost;
                }
            }
            dp[l][j] = m;
        }
        F0R(i, n) F0R(j, k) if(dp[i][j] != -1 && (dp[i][j] < minCost || minCost == -1)) minCost = dp[i][j];
    }
    fout << minCost << "\n";
    return 0;
}
