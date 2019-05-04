#include <bits/stdc++.h>

#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FOR(i, a, b) for (int i = (a); i < (b); i++)

#define INF 1e18

using namespace std;

typedef long long ll;

#define MAXN 400

int n, k;
ll a[MAXN], dp[MAXN + 1][MAXN + 1];

int main() {
	ifstream cin("snakes.in");
	ofstream cout("snakes.out");
	cin >> n >> k;
	F0R(i, n) cin >> a[i];
	F0R(i, n + 1) F0R(j, k + 2) dp[i][j] = INF;
	dp[0][0] = 0;
	F0R(i, n) F0R(j, k + 1) if(dp[i][j] != INF) {
		ll runSum = 0, runMax = 0;
		FOR(toAdd, 1, n + 1 - i) {
			runSum += a[i + toAdd - 1];
			runMax = max(runMax, a[i + toAdd - 1]);
			dp[i + toAdd][j + 1] = min(dp[i + toAdd][j + 1], dp[i][j] + toAdd * runMax - runSum);
		}
	}
	cout << dp[n][k + 1] << endl;
}
