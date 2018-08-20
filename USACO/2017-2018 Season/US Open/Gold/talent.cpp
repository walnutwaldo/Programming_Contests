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
#define MAXN 250
#define MAXW 1000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<ull> vul;
typedef complex<ld> point;

int N, W;
ll t[MAXN], w[MAXN], dp[MAXN + 1][MAXW + 1];

bool canAchieve(ll val) {
 	F0R(i, N + 1) F0R(j, W + 1) dp[i][j] = (1LL << 63);
	dp[0][0] = 0;
	F0R(i, N) {
		ll value = t[i] - val * w[i];
		F0R(j, W + 1) {
			if(dp[i][j] == (1LL << 63)) continue;
			int newWT = min(W, (int)(j + w[i]));
			dp[i + 1][newWT] = max(dp[i + 1][newWT], dp[i][j] + value);
			dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
		}
	}
	return dp[N][W] >= 0;
}

int main() {
	ifstream fin("talent.in");
	ofstream fout("talent.out");
	fin >> N >> W;
	ll lo = 0, hi = 0;
	F0R(i, N) {
		fin >> w[i] >> t[i];
		t[i] *= 1000;
		hi = max(hi, t[i] / w[i]);
	}
	while(lo < hi) {
		ll mid = (lo + hi + 1) >> 1;
		if(canAchieve(mid)) lo = mid;
		else hi = mid - 1;
	}
	fout << lo << endl;
}
