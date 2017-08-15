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
#define MAXN 100000
#define LEFT 1
#define RIGHT 2
#define TOTALDIS 1000000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ll> point;

int n;
ll x[MAXN], v[MAXN];
int dir[MAXN];
ll s;

bool possible(ld t) {
    vector<pair<ll,ll>> segments;
    F0R(i, n) {
        if(dir[i] == LEFT) {
            ll p = (ll)((ld)((s + v[i]) * (s - v[i]) * t + v[i] * x[i])/(s));
            if((ld)x[i]/v[i] <= t) segments.PB(MP(0, TOTALDIS));
            else if(p >= x[i]) segments.PB(MP(x[i], p));
        }
    }
    F0R(i, n) {
        if(dir[i] == RIGHT) {
            ll p = TOTALDIS - (ll)((ld)((s + v[i]) * (s - v[i]) * t + v[i] * (TOTALDIS - x[i]))/(s));
            if((ld)(TOTALDIS - x[i])/v[i] <= t) return segments.size();
            else if(p <= x[i]) {
                for(const pair<ll, ll> segment : segments) {
                    if(p <= segment.S && x[i] >= segment.F) return true;
                }
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> s;
    F0R(i, n) cin >> x[i] >> v[i] >> dir[i];
    ld lo = 0;
    ld hi = TOTALDIS;
    F0R(counter, 45) {
        ld mid = (lo + hi) / 2;
        if(possible(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    cout << fixed << setprecision(12) << lo << "\n";
    return 0;
}
