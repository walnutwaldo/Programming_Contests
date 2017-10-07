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
typedef complex<ld> point;

int n, m, q[MAXN], numOpen = 1, parent[MAXN], sizeRootedAt[MAXN];
bool ans[MAXN], open[MAXN];
vi connections[MAXN];

int root(int node) {
    if(parent[node] != node) parent[node] = root(parent[node]);
    return parent[node];
}

void join(int node1, int node2) {
    int r1 = root(node1),  r2 = root(node2);
    if(r1 == r2) return;
    if(sizeRootedAt[r1] < sizeRootedAt[r2]) swap(r1, r2);
    sizeRootedAt[r1] += sizeRootedAt[r2];
    parent[r2] = r1;
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
    F0R(i, n) parent[i] = i;
    F0R(i, n) sizeRootedAt[i] = 1;
    numOpen = 1;
    open[q[n - 1]] = 1;
    ans[n - 1] = 1;
    R0F(i, n - 1) {
        int barn = q[i];
        numOpen++;
        open[barn] = true;
        for(const int conn : connections[barn]) {
            if(open[conn]) join(conn, barn);
        }
        ans[i] = numOpen == sizeRootedAt[root(barn)];
    }
    F0R(i, n) {
        if(ans[i]) fout << "YES\n";
        else fout << "NO\n";
    }
    return 0;
}
