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
#define MOD 1000000007

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, k, color[MAXN];
vi connections[MAXN];
ll dp[MAXN][3];

void dfs(int node, int parent) {
    vector<ll> numWays[3];
    for(const int next : connections[node]) {
        if(next == parent) continue;
        dfs(next, node);
        numWays[0].PB((dp[next][1] + dp[next][2]) % MOD);
        numWays[1].PB((dp[next][0] + dp[next][2]) % MOD);
        numWays[2].PB((dp[next][0] + dp[next][1]) % MOD);
    }
    F0R(i, 3) {
        if(color[node] != 0 && color[node] != i + 1) continue;
        dp[node][i] = 1;
        for(const ll l : numWays[i]) dp[node][i] = (dp[node][i] * l) % MOD;
    }
}

int main() {
    ifstream fin("barnpainting.in");
    ofstream fout("barnpainting.out");
    fin >> n >> k;
    F0R(i, n - 1) {
        int a, b;
        fin >> a >> b;
        a--, b--;
        connections[a].PB(b);
        connections[b].PB(a);
    }
    F0R(i, k) {
        int a;
        fin >> a;
        a--;
        fin >> color[a];
    }
    dfs(0, -1);
    fout << (dp[0][0] + dp[0][1] + dp[0][2]) % MOD << "\n";
    return 0;
}
