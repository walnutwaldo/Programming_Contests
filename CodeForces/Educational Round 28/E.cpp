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
#define MOD 1000000007

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n;
ll a[MAXN], b[MAXN];
vector<pair<int, ll>> connections[MAXN];

pair<ll, ll> needed(int node) {
    ll temp = a[node] - b[node];
    ll temp2 = temp / MOD;
    temp %= MOD;
    for(const pii edge : connections[node]) {
        pair<ll, ll> curr = needed(edge.F);
        if(curr.F > 0 || curr.F == 0 && curr.S >= 0) {
            curr.F *= edge.S;
            curr.S *= edge.S;
        }
        temp += curr.S;
        temp2 += temp / MOD;
        temp %= MOD;
        temp2 += curr.F;
    }
    return MP(temp2, temp);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    F0R(i, n) cin >> b[i];
    F0R(i, n) cin >> a[i];
    F0R(i, n - 1) {
        int x;
        ll k;
        cin >> x >> k;
        connections[--x].PB(MP(i + 1, k));
    }
    pair<ll, ll> res = needed(0);
    if(res.F <= 0 && res.S <= 0) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}
