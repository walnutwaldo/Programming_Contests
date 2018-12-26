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

#define PRIME 1000000007

int n;

unordered_map<ll, int> cnt;

ll getHash(const vi& v, int mask) {
    ll res = 0;
    F0R(i, 5) if((mask >> i) & 1) {
        res *= PRIME;
        res += v[i];
    }
    return res;
}

int main() {
    ifstream fin("cowpatibility.in");
    ofstream fout("cowpatibility.out");
    fin >> n;
    ll res = 0;
    F0R(i, n) {
        vi v;
        F0R(j, 5) {
            int f;
            fin >> f;
            v.PB(f);
        }
        sort(all(v));
        F0R(j, 32) {
            ll h = getHash(v, j);
            if(__builtin_popcount(j) & 1) res -= cnt[h];
            else res += cnt[h];
            cnt[h]++;
        }
    }
    fout << res << endl;
}
