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

#define MOD 1000000007
#define MAXN 5000

int n, m, k;
vi withRC[MAXN];
ll rcres[MAXN], withS[MAXN + 1];
ll dp[MAXN + 1];
int cnt[26];

void mmult(ll& a, ll b) { a = (a * b) % MOD; }

void madd(ll& a, ll b) { a = (a + b) % MOD; }

ll modPow(ll a, ll p) {
    return p?((p & 1)? a * modPow(a, p - 1) % MOD: modPow(a * a % MOD, p >> 1)):1;
}

int main() {
    ifstream cin("poetry.in");
    ofstream cout("poetry.out");
    cin >> n >> m >> k;
    dp[0] = 1;
    F0R(i, n) {
        int s, c;
        cin >> s >> c;
        withRC[c - 1].PB(s);
        withS[s]++;
    }
    dp[0] = 1;
    F0R(i, k) {
        F0R(j, k + 1) if(i + j <= k) madd(dp[i + j], dp[i] * withS[j] % MOD);
    }
    F0R(i, n) {
        for(const int s : withRC[i]) {
            madd(rcres[i], dp[k - s]);
        }
    }
    F0R(i, m) {
        char c;
        cin >> c;
        cnt[c - 'A']++;
    }
    ll res = 1;
    F0R(i, 26) {
        ll tomult = 0;
        if(cnt[i]) {
            F0R(j, n) madd(tomult, modPow(rcres[j], cnt[i]));
        } else tomult = 1;
        mmult(res, tomult);
    }
    cout << res << endl;
}
