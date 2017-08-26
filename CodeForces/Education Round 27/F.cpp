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
#define MOD 1000000007

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ll> point;

char grid[250][250];
int colMask[250];
int n, m;
ll res;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    if(n > m) {
        F0R(i, n) F0R(j, m) cin >> grid[j][i];
        swap(n, m);
    } else F0R(i, n) F0R(j, m) cin >> grid[i][j];
    F0R(c, m) F0R(r, n) if(grid[r][c] == 'x') colMask[c] |= (1 << r);

    ll dp[n][m][1 << n][2][2];
    memset(dp, 0, sizeof dp);
    dp[0][0][colMask[0]][0][0] = 1;

    F0R(c, m) F0R(r, n) F0R(mask, 1 << n) F0R(protectedAbove, 2) F0R(oneNotProtected, 2) {
        if(r == n - 1 && c == m - 1) {
            if(protectedAbove || (mask & 1 << r) || !oneNotProtected) res += dp[r][c][mask][protectedAbove][oneNotProtected];
            if(grid[r][c] == '.') res += dp[r][c][mask][protectedAbove][oneNotProtected];
            res %= MOD;
        } else {
            int nextR = (r + 1) % n;
            int nextC = c + (nextR == 0);
            int nextMask = mask;
            if(nextC > c) {
                nextMask &= ~colMask[c];
                nextMask |= colMask[nextC];
            }
            if(grid[r][c] == 'x') {
                dp[nextR][nextC][nextMask][0][oneNotProtected] += dp[r][c][mask][protectedAbove][oneNotProtected];
                dp[nextR][nextC][nextMask][0][oneNotProtected] %= MOD;
            } else {
                dp[nextR][nextC][nextMask | (1 << r)][nextC == c][oneNotProtected] += dp[r][c][mask][protectedAbove][oneNotProtected];
                dp[nextR][nextC][nextMask | (1 << r)][nextC == c][oneNotProtected] %= MOD;
                if((mask & (1 << r)) || protectedAbove || !oneNotProtected) {
                    dp[nextR][nextC][nextMask][protectedAbove && (nextC == c)][oneNotProtected || !((mask & (1 << r)) || protectedAbove)] += dp[r][c][mask][protectedAbove][oneNotProtected];
                    dp[nextR][nextC][nextMask][protectedAbove && (nextC == c)][oneNotProtected || !((mask & (1 << r)) || protectedAbove)] %= MOD;
                }
            }
        }
    }
    cout << res << endl;
    return 0;
}
