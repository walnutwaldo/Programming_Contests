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
#define MAXN 1000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, dp[MAXN + 1][MAXN + 1], cowAt[MAXN + 1], posRight[MAXN + 1];

int main() {
    ifstream fin("nocross.in");
    ofstream fout("nocross.out");

    int maximum = 0;
    fin >> n;
    FOR(i, 1, n + 1) {
        fin >> cowAt[i];
    }
    FOR(i, 1, n + 1) {
        int j;
        fin >> j;
        posRight[j] = i;
    }
    FOR(i, 1, n + 1) {
        FOR(j, max(1, cowAt[i] - 4), min(n, cowAt[i] + 4) + 1) {
            dp[i][posRight[j]] = 1;
        }
    }
    FOR(j, 1, n + 1) FOR(i, 1, n + 1) dp[i][j] = max(max(dp[i - 1][j], dp[i][j-1]), dp[i][j] + dp[i - 1][j - 1]);
    fout << dp[n][n] << endl;
    return 0;
}
