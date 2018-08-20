#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (a) - 1; i >= (b); i--)

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define MAXN 50000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, k, ancestor[MAXN + 1][17], flow[MAXN + 1], depth[MAXN + 1], maxFlow;
vi children[MAXN + 1], connections[MAXN + 1];

int ancestorAtDepth(int node, int wantedDepth) {
    int changes = depth[node] - wantedDepth;
    int p = 0;
    while(changes > 0) {
        if(changes & 1) node = ancestor[node][p];
        changes >>= 1;
        p++;
    }
    return node;
}

int commonAncestor(int a, int b) {
    if(depth[a] > depth[b]) return commonAncestor(b, a);
    if(depth[b] > depth[a]) b = ancestorAtDepth(b, depth[a]);
    R0F(curr, 17) {
        if(ancestor[b][curr] != ancestor[a][curr]){
            b = ancestor[b][curr];
            a = ancestor[a][curr];
        }
    }
    while(a != b) {
        a = ancestor[a][0];
        b = ancestor[b][0];
    }
    return a;
}

void calcFlow(int node) {
    for(const int child: children[node]) {
        calcFlow(child);
        flow[node] += flow[child];
    }
    maxFlow = max(maxFlow, flow[node]);
}

void dfs(int node, int par, int d) {
    ancestor[node][0] = par;
    depth[node] = d;
    for(const int conn: connections[node]){
        if(conn == par) continue;
        children[node].PB(conn);
        dfs(conn, node, d + 1);
    }
}

int main() {
    ifstream fin("maxflow.in");
    ofstream fout("maxflow.out");
    fin >> n >> k;
    F0R(i, n - 1) {
        int a, b;
        fin >> a >> b;
        connections[a].PB(b);
        connections[b].PB(a);
    }
    dfs(1, 0, 0);
    FOR(i, 1, 17) FOR(j, 1, n + 1) ancestor[j][i] = ancestor[ancestor[j][i - 1]][i - 1];
    F0R(i, k) {
        int a, b;
        fin >> a >> b;
        int c = commonAncestor(a, b);
        flow[a]++;
        flow[b]++;
        flow[c]--;
        flow[ancestor[c][0]]--;
    }
    calcFlow(1);
    fout << maxFlow << "\n";
    return 0;
}
