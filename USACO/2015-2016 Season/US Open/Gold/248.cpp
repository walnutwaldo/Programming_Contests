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
#define MAXN 248

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n, dp[MAXN][MAXN];

int main() {
    ifstream fin("248.in");
    ofstream fout("248.out");
    fin >> n;
    int res = 0;
    F0R(i, n) {
        fin >> dp[i][i];
        res = max(res, dp[i][i]);
    }
    FOR(length, 1, n) {
        F0R(s, n - length) {
            int e = s + length;
            FOR(i, s, e) {
                if(dp[s][i] == dp[i + 1][e]) dp[s][e] = max(dp[s][e], dp[s][i] + 1);
                res = max(res, dp[s][e]);
            }
        }
    }
    fout << res << "\n";
    return 0;
}
