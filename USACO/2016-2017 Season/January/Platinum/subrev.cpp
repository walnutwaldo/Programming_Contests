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
#define MAXN 50

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int N, a[MAXN], dp[MAXN][MAXN][51][51];

int solve(int i, int j, int k, int m) {
    if (dp[i][j][k][m] != -1) return dp[i][j][k][m];
    if (k > m) return -(1 << 29); // impossible case
    if (i > j) return 0;
    if (i == j) {
        if (a[i] >= k && a[i] <= m) return 1;
        else return 0;
    }
    // max value from interval [i,j] given we've taken k from prefix and m from suffix
    int res = 0;
    // case 1: swap i and j
    // case 1a: don't include a[i] or a[j]
    res = max(res, solve(i+1,j-1,k,m));
    // case 1b: include a[j]
    if (a[j] >= k)
        res = max(res, solve(i+1,j-1,a[j],m)+1);
    // case 1c: include a[i]
    if (a[i] <= m)
        res = max(res, solve(i+1,j-1,k,a[i])+1);
    // case 1d: include both
    if (k <= a[j] && a[j] <= a[i] && a[i] <= m) {
        res = max(res, solve(i+1,j-1,a[j],a[i])+2);
    }

    // case 2: don't swap, move i forward
    // case 2a: don't include a[i]
    res = max(res, solve(i+1,j,k,m));
    // case 2b: include a[i]
    if (a[i] >= k)
        res = max(res, solve(i+1,j,a[i],m)+1);

    // case 3: don't swap, move j backward
    // case 3a: don't include a[j]
    res = max(res, solve(i,j-1,k,m));
    // case 3b: include a[j]
    if (a[j] <= m)
        res = max(res, solve(i,j-1,k,a[j])+1);

    return dp[i][j][k][m] = res;
}

int main() {
    ifstream fin("subrev.in");
    ofstream fout("subrev.out");

    fin >> N;
    F0R(i, N) fin >> a[i];
    F0R(i, N) F0R(j, N) F0R(k, 51) F0R(l, 51) dp[i][j][k][l] = -1;

    fout << solve(0, N - 1, 0, 50) << endl;
    return 0;
}
