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
#define MAXN 200000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ll> point;

int n, val[MAXN], best[MAXN];
vi connections[MAXN];

void dfs(int node, int par, int prefixGCD, set<int> soFar) {
    best[node] = prefixGCD;
    set<int> nextSoFar;
    for(const int i : soFar) {
        int temp = __gcd(val[node], i);
        nextSoFar.insert(temp);
        best[node] = max(best[node], temp);
    }
    nextSoFar.insert(prefixGCD);
    prefixGCD = __gcd(prefixGCD, val[node]);
    for(const int conn : connections[node]) {
        if(conn == par) continue;
        dfs(conn, node, prefixGCD, nextSoFar);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    F0R(i, n) cin >> val[i];
    F0R(i, n - 1) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        connections[a].PB(b);
        connections[b].PB(a);
    }
    dfs(0, -1, 0, {});
    cout << val[0];
    FOR(i, 1, n) cout << " " << best[i];
    cout << "\n";
    return 0;
}
close
