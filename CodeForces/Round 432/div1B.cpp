// cheap solution
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
ll x, y;
bool composite[MAX + 1];
int occurences[MAX + 1], a[MAXN];
vector<pii> v;

ll cost(int p) {
    ll total = 0;
    F0R(i, n) total += min(x, y * (ll)(ceil((double)a[i] / p) * p - a[i]));
    return total;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    FOR(i, 2, MAX + 1) if(!composite[i]) for(int j = 2 * i; j <= MAX; j += i) composite[j] = true;
    cin >> n >> x >> y;
    F0R(i, n) {
        cin >> a[i];
        occurences[a[i]]++;
    }
    FOR(i, 2, MAX + 1) if(!composite[i]) {
        int total = 0;
        for(int j = i; j <= MAX; j += i) total += occurences[j] + occurences[j - 1];
        v.PB(MP(total, i));
    }
    sort(v.rbegin(), v.rend());
    ll ans = -1;
    F0R(i, 4) {
        ll temp = cost(v[i].S);
        if(ans == -1 || temp < ans) ans = temp;
    }
    cout << ans << "\n";
    return 0;
}
