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
#define MAXN 100000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n;
vi connections[MAXN];
ld expected[MAXN];

void dfs(int node, int parent) {
    ll options = 0;
    for(const int next: connections[node]) {
        if(next == parent) continue;
        dfs(next, node);
        expected[node] += (1 + expected[next]);
        options++;
    }
    if(options > 0) expected[node] /= options;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    F0R(i, n - 1) {
        int a, b;
        cin >> a >> b;
        connections[a - 1].PB(b - 1);
        connections[b - 1].PB(a - 1);
    }
    dfs(0, -1);
    cout << fixed;
    cout << setprecision(9) << expected[0] << "\n";
    return 0;
}
