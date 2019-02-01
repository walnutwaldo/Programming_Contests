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

#define INF 1e18
#define PI acos(-1)

#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define SQ(x) ((x) * (x))

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef vector<ll> vll;
typedef vector<ull> vul;
typedef complex<ld> point;
typedef complex<ld> cld;
typedef vector<cld> vcld;

#define MAXV 1000000000
#define MOD 1000000007

#define MAXN 100000

int n, k, m;
ll winMin[MAXN], minV[MAXN];
bool isSet[MAXN];
vector<pair<ll, int>> unsetRanges;

void calcMinV() {
    deque<pii> q;
    F0R(i, n) {
        if(q.front().S == i - k) q.pop_front();
        while(i < m && !q.empty() && q.back().F <= winMin[i]) q.pop_back();
        q.push_back(MP(winMin[i], i));
        minV[i] = q.front().F;
    }
}

void calcUnsetRanges() {
    ll curr = -1;
    int running = 0;
    F0R(i, n) {
        if(isSet[i]) {
            if(curr != -1) unsetRanges.PB(MP(curr, running));
            curr = -1;
            running = 0;
        } else {
            curr = minV[i];
            running++;
        }
    }
    if(curr != -1) unsetRanges.PB(MP(curr, running));
}

ll dp[MAXN + 2];

ll modPow(ll a, int p) {
    if(p == 0) return 1;
    if(p & 1) return a * modPow(a, p - 1) % MOD;
    return modPow(a * a % MOD, p >> 1);
}

ll solve(ll a, int cnt) {
    dp[0] = dp[1] = 1;
    ll powVma = modPow(MAXV - a, k);
    FOR(i, 2, cnt + 2) {
        dp[i] = (MAXV - a + 1) * dp[i - 1] % MOD;
        if(i - k - 1 >= 0) dp[i] = (dp[i] + MOD - dp[i - k - 1] * powVma % MOD) % MOD;
    }
    return dp[cnt + 1];
}

int main() {
    ifstream cin("tracking2.in");
    ofstream cout("tracking2.out");
    cin >> n >> k;
    m = n - k + 1;
    F0R(i, m) cin >> winMin[i];
    calcMinV();
    F0R(i, n - 1) if(minV[i] != minV[i + 1]) isSet[(minV[i] < minV[i + 1])? i : i + 1] = 1;
    calcUnsetRanges();
    ll res = 1;
    for(const pair<ll, int> p : unsetRanges) res = (res * solve(p.F, p.S)) % MOD;
    cout << res << endl;
}
