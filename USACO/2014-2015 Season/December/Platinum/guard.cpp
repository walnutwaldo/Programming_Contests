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
#define INF 1e15

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

#define MAXN 20

int n;
ll h, height[MAXN], weight[MAXN], strength[MAXN], maxSafety[1 << MAXN];

ll solve(int mask) {
    if(mask == 0) return INF;
    if(maxSafety[mask] != -INF) return maxSafety[mask];
    int temp = mask;
    while(temp) {
        int x = temp & -temp;
        temp ^= x;
        int i = 31 - __builtin_clz(x);
        ll ms = solve(mask ^ x);
        maxSafety[mask] = max(maxSafety[mask], min(ms - weight[i], strength[i]));
    }
    return maxSafety[mask];
}

int main() {
    ifstream cin("guard.in");
    ofstream cout("guard.out");
    cin >> n >> h;
    F0R(i, n) cin >> height[i] >> weight[i] >> strength[i];
    F0R(i, 1 << n) maxSafety[i] = -INF;
    ll res = -INF;
    F0R(mask, 1 << n) {
        ll totalH = 0;
        F0R(i, n) if((mask >> i) & 1) totalH += height[i];
        if(totalH < h) continue;
        res = max(res, solve(mask));
    }
    if (res < 0) cout << "Mark is too tall" << endl;
    else cout << res << endl;
}
