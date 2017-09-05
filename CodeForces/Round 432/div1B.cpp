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
#define MAXN 500000
#define MAX 1000000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n;
bool composite[MAX + 1];
ll x, y, sumTo[MAX + 1], prefixCnt[MAX + 1];
int mostChange;

ll cnt(int l, int r) {
    if(r < l) return 0;
    if(r < 0) return 0;
    if(l > MAX) return 0;
    r = min(r, MAX);
    l = min(l, MAX);
    if(l <= 0) return prefixCnt[r];
    else return prefixCnt[r] - prefixCnt[l - 1];
}

ll sum(int l, int r) {
    if(r < l) return 0;
    if(r < 0) return 0;
    if(l > MAX) return 0;
    r = min(r, MAX);
    if(l <= 0) return sumTo[r];
    else return sumTo[r] - sumTo[l - 1];
}

ll cost(int p) {
    ll total = 0;
    for(int j = p; j - p + 1 <= MAX; j += p) {
        int f = max(j - p + 1, j - mostChange);
        total += x * cnt(j - p + 1, f - 1);
        total += y * (cnt(f, j) * j - sum(f, j));
    }
    return total;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    FOR(i, 2, MAX + 1) if(!composite[i]) for(int j = 2 * i; j <= MAX; j += i) composite[j] = true;
    cin >> n >> x >> y;
    mostChange = x / y;
    F0R(i, n) {
        ll a;
        cin >> a;
        sumTo[(int)a] += a;
        prefixCnt[(int)a]++;
    }
    FOR(i, 1, MAX + 1) {
        sumTo[i] += sumTo[i - 1];
        prefixCnt[i] += prefixCnt[i - 1];
    }
    ll ans = -1;
    FOR(i, 2, MAX + 1) if(!composite[i]) {
        ll temp = cost(i);
        if(ans == -1 || temp < ans) ans = temp;
    }
    cout << ans << "\n";
    return 0;
}
