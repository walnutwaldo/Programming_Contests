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
#define MAXN 300
#define MOD 1000000007

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ll> point;

int n;
ll a[MAXN];
bool isMain[MAXN];
int available[MAXN];
int numClasses;
vector<int> classes;
ll dp[MAXN + 1][MAXN];
ll C[MAXN + 1][MAXN + 1];
ll fact[MAXN + 1];
bool solvedC[MAXN + 1][MAXN + 1];
bool solvedF[MAXN + 1];

ll choose(int i, int j) {
    if(i < 0 || j < 0 || j > i) return 0;
    if(solvedC[i][j]) return C[i][j];
    if(solvedC[i][i - j]) {
        C[i][j] = C[i][i - j];
    } else if(i == 0) {
        C[i][j] = 1;
    } else {
        C[i][j] = (choose(i - 1, j) + choose(i - 1, j - 1)) % MOD;
    }
    solvedC[i][j] = true;
    return C[i][j];
}

ll factorial(int i) {
    if(solvedF[i]) return fact[i];
    if(i == 0) fact[i] = 1;
    else fact[i] = (i * factorial(i - 1)) % MOD;
    solvedF[i] = true;
    return fact[i];
}

bool isSquare(ll s) {
    ll sq = (ll)round(sqrt(s));
    return SQ(sq) == s;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    F0R(i, n) {
        cin >> a[i];
        isMain[i] = true;
        available[i] = 1;
        F0R(j, i) {
            if(isSquare(a[j] * a[i])) {
                isMain[i] = false;
                available[j]++;
                break;
            }
        }
    }
    F0R(i, n) {
        if(isMain[i]) {
            numClasses++;
            classes.PB(available[i]);
        }
    }
    int numSoFar = classes[0];
    dp[0][classes[0] - 1] = factorial(classes[0]);
    FOR(i, 1, numClasses) {
        int nextSoFar = numSoFar + classes[i];
        F0R(j, nextSoFar) {
            F0R(k, numSoFar) {
                F0R(numKeep, min(j + 1, k + 1)) {
                    int numSpent = k - numKeep;
                    int stillHave = classes[i] - numSpent;
                    int numNew = j - numKeep;
                    if(numNew > stillHave) continue;
                    int canFill = numSoFar + 1 - k;
                    dp[i][j] += ((((((dp[i - 1][k] * choose(k, numSpent))%MOD) * choose(canFill, stillHave - numNew))%MOD) * choose(classes[i] - 1, classes[i] - numNew - 1))%MOD * factorial(classes[i]))%MOD;
                    dp[i][j] %= MOD;
                }
            }
        }
        numSoFar = nextSoFar;
    }
    cout << dp[numClasses - 1][0] << "\n";
    return 0;
}
