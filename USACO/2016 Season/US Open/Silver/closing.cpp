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
#define MAXN 3000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n, m, q[MAXN], numOpen, numCounted;
bool ans[MAXN], on[MAXN], seen[MAXN];
vi connections[MAXN];

void dfs(int node) {
    seen[node] = true;
    numCounted++;
    for(const int conn : connections[node]) if(on[conn] && !seen[conn]) dfs(conn);
}

bool connected() {
    memset(seen, 0, sizeof seen);
    numCounted = 0;
    dfs(q[n - 1]);
    return numCounted == numOpen;
}

int main() {
    ifstream fin("closing.in");
    ofstream fout("closing.out");
    fin >> n >> m;
    F0R(i, m) {
        int a, b;
        fin >> a >> b;
        a--, b--;
        connections[a].PB(b);
        connections[b].PB(a);
    }
    F0R(i, n) {
        fin >> q[i];
        q[i]--;
    }
    on[q[n - 1]] = 1;
    numOpen = 1;
    ans[n - 1] = true;
    R0F(i, n - 1) {
        int barn = q[i];
        on[barn] = true;
        numOpen++;
        ans[i] = connected();
    }
    F0R(i, n) {
        if(ans[i]) fout << "YES\n";
        else fout << "NO\n";
    }
    return 0;
}
