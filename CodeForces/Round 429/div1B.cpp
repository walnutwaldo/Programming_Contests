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
#define MAXN 300000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ll> point;

int n, m, parity, neg = -1;
int val[MAXN];
bool visited[MAXN];
bool inAnswer[MAXN];
bool inTree[MAXN];
vector<pii> connections[MAXN];
vector<pii> children[MAXN];

void dfs(int node) {
    for(const pii edge : children[node]) {
        dfs(edge.F);
        if(val[edge.F] == 1) val[node] ^= 1, val[edge.F] ^= 1, inAnswer[edge.S] = true;
    }
}

void treeify(int node) {
    inTree[node] = true;
    for(const pii edge : connections[node]) {
        if(inTree[edge.F]) continue;
        children[node].PB(edge);
        treeify(edge.F);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    F0R(i, n) {
        cin >> val[i];
        if(val[i] == 1) parity ^= 1;
        if(val[i] == -1) {
            neg = i;
            val[i] = 0;
        }
    }
    if(parity) {
        if(neg == -1) {
            cout << "-1\n";
            return 0;
        }
        val[neg] = 1;
    }
    F0R(i, m) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        connections[a].PB(MP(b, i));
        connections[b].PB(MP(a, i));
    }
    treeify(0);
    dfs(0);
    int k = 0;
    F0R(i, m) if(inAnswer[i]) k++;
    cout << k << "\n";
    F0R(i, m) if(inAnswer[i]) cout << i + 1 << "\n";
    return 0;
}
