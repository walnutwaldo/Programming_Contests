#include <bits/stdc++.h>

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

#define PI acos(-1)

#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define SQ(x) ((x) * (x))

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef vector<ll> vll;
typedef vector<ull> vul;
typedef complex<ld> point;
typedef complex<ld> cld;
typedef vector<cld> vcld;

#define MAXN 100
#define MOD 1000000007

int r, c, k;
ll a[MAXN][MAXN], dp[MAXN][MAXN];

void madd(ll& a, ll b) { a = (a + b) % MOD; }

int main() {
    ifstream fin("hopscotch.in");
    ofstream fout("hopscotch.out");
    fin >> r >> c >> k;
    F0R(i, r) F0R(j, c) {
        fin >> a[i][j];
        a[i][j]--;
    }
    dp[r - 1][c - 1] = 1;
    R0F(i, r - 1) R0F(j, c - 1) FOR(col, j + 1, c) FOR(row, i + 1, r) if(a[row][col] != a[i][j]) madd(dp[i][j], dp[row][col]);
    fout << dp[0][0] << endl;
}
