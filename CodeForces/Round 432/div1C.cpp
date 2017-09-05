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
#define MAXN 100

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n, a[MAXN];
unordered_map<int, int> primes, grundy;

int getGrundy(int mask) {
    if(grundy.count(mask)) return grundy[mask];
    unordered_set<int> seen;
    F0R(i, 31) {
        if(mask < (1 << i)) continue;
        int a = mask >> (i + 1);
        int b = mask & ((1 << i) - 1);
        seen.insert(getGrundy(a | b));
    }
    int i = -1;
    while(seen.count(++i)) {}
    grundy[mask] = i;
    return i;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    F0R(i, n) {
        cin >> a[i];
        int b = a[i];
        if((b & 1) == 0) {
            int c = 0;
            while((b & 1) == 0) {
                b >>= 1;
                c++;
            }
            primes[2] |= (1 << (c - 1));
        }
        for(int j = 3; j * j <= b; j += 2) {
            if(b % j == 0) {
                int c = 0;
                while(b % j == 0) {
                    b /= j;
                    c++;
                }
                primes[j] |= (1 << (c - 1));
            }
        }
        if(b > 1) primes[b] |= 1;
    }
    grundy[0] = 0;
    int totalXOR = 0;
    for(const auto p : primes) {
        totalXOR ^= getGrundy(p.S);
    }
    if(totalXOR == 0) cout << "Arpa\n";
    else cout << "Mojtaba\n";
    return 0;
}
