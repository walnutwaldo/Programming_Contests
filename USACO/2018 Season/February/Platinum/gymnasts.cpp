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
#define MOD 1000000007

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

ll n;
vector<ll> primeFactors;

ll totient(ll a) {
    ll res = a;
    for(const ll f : primeFactors)
        if(a % f == 0)
            res = res / f * (f - 1);
    return res;
}

ll modPow(ll a, ll p) { return p? ((p & 1)? a * modPow(a, p ^ 1) % MOD : modPow(SQ(a) % MOD, p >> 1)) : 1; }

int main() {
    ifstream fin("gymnasts.in");
    ofstream fout("gymnasts.out");
    fin >> n;

    ll temp = n;
    for(ll i = 2; i * i <= temp; i++)
        if(temp % i == 0) {
            primeFactors.PB(i);
            while(temp % i == 0)
                temp /= i;
        }
    if(temp != 1)
        primeFactors.PB(temp);

    ll res = (2 - n + 2 * MOD - modPow(2, n)) % MOD;
    for(ll i = 1; i * i <= n; i++)
        if(n % i == 0) {
            res += (modPow(2, i) * totient(n / i)) % MOD;
            if(n / i != i)
                res += (modPow(2, n / i) * totient(i)) % MOD;
            res %= MOD;
        }
    fout << res << endl;
    return 0;
}
