#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MOD 1000000007

#define MAXN 2001

int n;
char grid[MAXN][MAXN];
int up[MAXN][MAXN], fromLeft[MAXN][MAXN];
ll pow2[MAXN + 1];
ll dp[MAXN + 1][MAXN + 1][2]; // 0 = from left, 1 = from up

void madd(ll& a, ll b) { a = (a + b) % MOD; }

int main() {
    ifstream fin("sprinklers2.in");
    ofstream fout("sprinklers2.out");
    fin >> n;
    pow2[0] = 1;
    for (int i = 1; i <= n; i++) { pow2[i] = (2 * pow2[i - 1]) % MOD; }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> grid[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '.') {
                up[i][j]++;
                fromLeft[i][j]++;
            }
            if (i > 0) { up[i][j] += up[i - 1][j]; }
            if (j > 0) { fromLeft[i][j] += fromLeft[i][j - 1]; }
        }
    }
    dp[1][0][1] = 1;
    dp[0][1][0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            // from left
            if (dp[i][j][0] != 0) {
                if (j < n) { // moving right
                    ll toadd = dp[i][j][0];
                    if (i > 0) { toadd = (toadd * pow2[up[i - 1][j]]) % MOD; }
                    madd(dp[i][j + 1][0], toadd);
                }
                if (i < n && grid[i][j - 1] == '.') { // moving down
                    ll toadd = dp[i][j][0];
                    toadd = (toadd * pow2[fromLeft[i][j - 1] - 1]) % MOD;
                    madd(dp[i + 1][j][1], toadd);
                }
            }
            // from up
            if (dp[i][j][1] != 0) {
                if (j < n && grid[i - 1][j] == '.') { // moving right
                    ll toadd = dp[i][j][1];
                    toadd = (toadd * pow2[up[i - 1][j] - 1]) % MOD;
                    madd(dp[i][j + 1][0], toadd);
                }
                if (i < n) { // moving down
                    ll toadd = dp[i][j][1];
                    toadd = (toadd * pow2[fromLeft[i][j - 1]]) % MOD;
                    madd(dp[i + 1][j][1], toadd);
                }
            }
        }
    }
    fout << (dp[n][n][0] + dp[n][n][1]) % MOD << endl;
}
