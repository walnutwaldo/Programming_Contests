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
#define MAXN 200000
#define MAXA 1000000
#define MOD 1000000007

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, occurences[MAXA + 1], multiplier[MAXA + 1];
ll answer, p2[MAXN + 1];

ll pow2(int p) {
    if(p == -1) return 0;
    if(p == 0) return 1;
    if(p == 1) return 2;
    if(p2[p] == 0) p2[p] = (pow2(p/2) * pow2((p + 1)/2)) % MOD;
    return p2[p];
}

void solve(int i) {
    multiplier[i] += i;
    int totalNumbers = 0;
    for(int j = i; j <= MAXA; j += i) totalNumbers += occurences[j];
    for(int j = 2 * i; j <= MAXA; j += i) multiplier[j] = (multiplier[j] - multiplier[i] + MOD) % MOD;
    answer = (answer + (multiplier[i] * ((totalNumbers * pow2(totalNumbers - 1)) % MOD)) % MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    F0R(i, n) {
        int a;
        cin >> a;
        occurences[a]++;
    }
    FOR(i, 2, MAXA + 1) {
        solve(i);
    }
    cout << answer << "\n";
    return 0;
}
