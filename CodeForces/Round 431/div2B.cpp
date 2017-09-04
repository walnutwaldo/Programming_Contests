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
#define MAXN 1000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n;
ll y[MAXN];

bool test(int f, int s) {
    ll dy = y[s] - y[f];
    ll dx = s - f;
    vi v;
    F0R(i, n) if(dy * (ll)(i - f) != dx * (y[i] - y[f])) v.PB(i);
    if(v.size() == 0) return 0;
    for(const int i : v) if(dy * (ll)(i - v[0]) != dx * (y[i] - y[v[0]])) return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    F0R(i, n) cin >> y[i];
    if(test(0, 1)) {
        cout << "YES\n";
        return 0;
    }
    if(test(1, 2)) {
        cout << "YES\n";
        return 0;
    }
    if(test(0, 2)) {
        cout << "YES\n";
        return 0;
    }
    cout << "NO\n";
    return 0;
}
