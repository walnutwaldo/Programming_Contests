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

struct RMQ {

    int sz;
    ll **tab;

    RMQ(ll* arr, int sz) {
        this->sz = sz;
        tab = new ll*[sz];
        int depth = 32 - __builtin_clz(sz);
        F0R(i, sz) tab[i] = new ll[depth];
        F0R(i, sz) tab[i][0] = arr[i];
        FOR(i, 1, depth) F0R(j, sz) tab[j][i] = max(tab[j][i - 1], tab[min(sz - 1, j + (1 << (i - 1)))][i - 1]);
    }

    ll query(int lo, int hi) {
        int d = 31 - __builtin_clz(hi - lo + 1);
        return max(tab[lo][d], tab[hi + 1 - (1 << d)][d]);
    }

};

#define MAXN 10000

int n, k;
ll arr[MAXN], dp[MAXN + 1];

int main() {
    ifstream fin("teamwork.in");
    ofstream fout("teamwork.out");
    fin >> n >> k;
    F0R(i, n) fin >> arr[i];
    RMQ rmq(arr, n);
    F0R(i, n) FOR(j, 1, k + 1) if(i + j <= n) dp[i + j] = max(dp[i + j], dp[i] + j * rmq.query(i, i + j - 1));
    fout << dp[n] << endl;
}
