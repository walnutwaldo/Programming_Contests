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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n;
unordered_map<int, int> lastOcc;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    ll total = (ll)n * n;
    ld res = 0;
    F0R(i, n) {
        int a;
        cin >> a;
        if(!lastOcc.count(a)) lastOcc[a] = -1;
        ll num = 2LL * (i - lastOcc[a]) * (n - i) - 1;
        res += (ld)num/total;
        lastOcc[a] = i;
    }
    cout << fixed << setprecision(9) << res << "\n";
    return 0;
}
