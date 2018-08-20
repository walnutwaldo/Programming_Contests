#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define ran() (rand() & 0x7FFF)
#define rand31() ((ran() << 16) | (ran() << 1) | (ran() & 1))
#define rand32() ((ran() << 17) | (ran() << 2) | (ran() & 3))
#define rand63() (((ll)ran() << 48) | ((ll)ran() << 33) | ((ll)ran() << 18) | ((ll)ran() << 3) | ((ll)ran() & 7))
#define rand64() (((ll)ran() << 49) | ((ll)ran() << 34) | ((ll)ran() << 19) | ((ll)ran() << 4) | ((ll)ran() & 15))

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define X real()
#define Y imag()
#define MAXN 100

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n, a[MAXN];
ll dp[MAXN][MAXN][MAXN + 1], least[MAXN][MAXN];

int main() {
    ifstream fin("taming.in");
    ofstream fout("taming.out");
    fin >> n;
    F0R(i, n) fin >> a[i];
    F0R(day, n) {
        dp[day][0][1] = a[day] != day;
        if(day > 0)
            dp[day][0][1] += dp[day - 1][0][1];
        least[day][1] = dp[day][0][1];
        FOR(lastBreakout, 1, n) dp[day][lastBreakout][1] = INT_MAX;
    }
    fout << dp[n - 1][0][1] << "\n";
    FOR(numBreakouts, 2, n + 1) {
        ll res = INT_MAX;
        F0R(day, n) {
            least[day][numBreakouts] = INT_MAX;
            F0R(lastBreakout, n) {
                dp[day][lastBreakout][numBreakouts] = (a[day] != day - lastBreakout) + dp[day - 1][lastBreakout][numBreakouts];
                if(lastBreakout < numBreakouts - 1 || lastBreakout > day || day < numBreakouts - 1) dp[day][lastBreakout][numBreakouts] = INT_MAX;
                least[day][numBreakouts] = min(least[day][numBreakouts], dp[day][lastBreakout][numBreakouts]);
            }
            dp[day][day][numBreakouts] = (a[day] != 0) + least[day - 1][numBreakouts - 1];
            if(day < numBreakouts - 1) dp[day][day][numBreakouts] = INT_MAX;
            least[day][numBreakouts] = min(least[day][numBreakouts], dp[day][day][numBreakouts]);
        }
        fout << least[n - 1][numBreakouts] << "\n";
    }
    return 0;
}
