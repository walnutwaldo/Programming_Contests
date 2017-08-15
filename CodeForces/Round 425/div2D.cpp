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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ll> point;

int n, q, ancestor[MAXN][17], depth[MAXN];
vi connection[MAXN];

int toDepth(int node, int d) {
    R0F(i, 17) while(depth[node] - (1 << i) >= d) node = ancestor[node][i];
    return node;
}

int lca(int a, int b) {
    if(depth[a] > depth[b]) return lca(b, a);
    if(depth[b] > depth[a]) return lca(a, toDepth(b, depth[a]));
    R0F(i, 17) if(ancestor[a][i] != ancestor[b][i]) {
        a = ancestor[a][i];
        b = ancestor[b][i];
    }
    if(a != b) {
        a = ancestor[a][0];
        b = ancestor[b][0];
    }
    return a;
}

void dfs(int node, int d) {
    depth[node] = d;
    for(const int conn: connection[node]) {
        if(conn == ancestor[node][0]) continue;
        ancestor[conn][0] = node;
        dfs(conn, d + 1);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    F0R(i, n - 1) {
        int c;
        cin >> c;
        connection[i + 1].PB(c - 1);
        connection[c - 1].PB(i + 1);
    }
    dfs(0, 0);
    FOR(p, 1, 17) F0R(i, n) ancestor[i][p] = ancestor[ancestor[i][p - 1]][p - 1];
    F0R(i, q) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        c--;
        int ab = lca(a, b), bc = lca(b, c), ac = lca(a, c);
        int lab = depth[a] + depth[b] - 2 * depth[ab];
        int lac = depth[a] + depth[c] - 2 * depth[ac];
        int lbc = depth[b] + depth[c] - 2 * depth[bc];
        int total = (lab + lac + lbc)/2;
        int answer = max(lab + lac, max(lbc + lab, lac + lbc)) - total + 1;
        assert(answer > 0);
        cout << answer << "\n";
    }
    return 0;
}
