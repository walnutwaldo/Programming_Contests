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
#define R real()
#define I image()
#define PI acos(-1)
#define MAXN 100000
#define MOD 1000000007

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;
typedef complex<ld> cld;

int n;
ll yVal[MAXN], w[MAXN], f[MAXN], fSqPrefix[MAXN], fPrefix[MAXN];

int main() {
    ifstream fin("sprinklers.in");
    ofstream fout("sprinklers.out");
    fin >> n;
    F0R(i, n) {
        int x, y;
        fin >> x >> y;
        yVal[x] = y;
    }
    w[0] = yVal[0];
    FOR(i, 1, n) w[i] = min(yVal[i], w[i - 1]);
    f[n - 1] = yVal[n - 1];
    R0F(i, n - 1) f[i] = max(yVal[i], f[i + 1]);
    fSqPrefix[0] = SQ(f[0]) % MOD;
    FOR(i, 1, n) fSqPrefix[i] = (fSqPrefix[i - 1] + SQ(f[i]) % MOD) % MOD;
    fPrefix[0] = f[0];
    FOR(i, 1, n) fPrefix[i] = (fPrefix[i - 1] + f[i] % MOD) % MOD;
    ll res = 0;
    int maxEnd = 0;
    F0R(s, n) {
        while(maxEnd < n - 1 && f[maxEnd + 1] > w[s]) maxEnd++;
        int numEnds = maxEnd - s;
        ll add = (fSqPrefix[maxEnd] + MOD - fSqPrefix[s]) % MOD;
        add += MOD - (2 * w[s] * ((fPrefix[maxEnd] + MOD - fPrefix[s]) % MOD)) % MOD;
        add %= MOD;
        add += numEnds * (SQ(w[s]) % MOD);
        add %= MOD;
        add += (fPrefix[maxEnd] + MOD - fPrefix[s]) % MOD;
        add %= MOD;
        add += MOD - (numEnds * w[s]) % MOD;
        add %= MOD;
        add = add * 500000004 % MOD;
        res = (res + add) % MOD;
    }
    fout << res << endl;
    return 0;
}
