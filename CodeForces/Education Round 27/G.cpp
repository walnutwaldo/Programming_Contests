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

int n, m, startingPathXOR, closest;
bool seen[MAXN], inTree[MAXN];
int toNode[MAXN];
tuple<int, int, int> allEdges[MAXN];
vector<tuple<int, int, int>> connections[MAXN];
vector<int> bases;

void dfs(int node, int xorSoFar) {
    toNode[node] = xorSoFar;
    seen[node] = true;
    if(node == n - 1) startingPathXOR = xorSoFar;
    for(const tuple<int, int, int> edge : connections[node]) {
        if(seen[get<0>(edge)]) continue;
        inTree[get<2>(edge)] = true;
        dfs(get<0>(edge), xorSoFar ^ get<1>(edge));
    }
}

bool canBeMade(int goal, int stop) {
    int vals[27];
    memset(vals, 0, sizeof vals);
    FOR(i, stop, 27) {
        F0R(j, bases.size()) if(bases[j] & (1 << i)) vals[i] |= (1 << j);
        if(goal & (1 << i)) vals[i] |= (1 << bases.size());
    }
    FOR(i, stop, 27) {
        if(vals[i] == (1 << bases.size())) return false;
        int firstBit = (vals[i] & -vals[i]);
        FOR(j, i + 1, 27) if(vals[j] & firstBit) vals[j] ^= vals[i];
    }
    return true;
}

void insertCycle(int cycleLength) {
    if(!canBeMade(cycleLength, 0)) bases.PB(cycleLength);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    F0R(i, m) {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        connections[a].PB(MT(b, w, i));
        connections[b].PB(MT(a, w, i));
        allEdges[i] = MT(a, b, w);
    }
    dfs(0, 0);
    F0R(i, m) if(!inTree[i]) insertCycle(toNode[get<0>(allEdges[i])] ^ toNode[get<1>(allEdges[i])] ^ get<2>(allEdges[i]));
    R0F(i, 27) {
        closest |= (startingPathXOR & (1 << i));
        if(!canBeMade(closest, i)) closest ^= (1 << i);
    }
    cout << (startingPathXOR ^ closest) << "\n";
    return 0;
}
