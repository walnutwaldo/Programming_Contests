#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define rand31() ((rand() << 16) | (rand() << 1) | (rand() & 1))
#define rand32() ((rand() << 17) | (rand() << 2) | (rand() & 3))
#define rand63() (((ll)rand() << 48) | ((ll)rand() << 33) | ((ll)rand() << 18) | ((ll)rand() << 3) | ((ll)rand() & 7))
#define rand64() (((ll)rand() << 49) | ((ll)rand() << 34) | ((ll)rand() << 19) | ((ll)rand() << 4) | ((ll)rand() & 15))

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define MAXN 200000
#define MAXK MAXN

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct DSU {

    int *parent;

    DSU(int sz) {
        parent = new int[sz];
        F0R(i, sz) parent[i] = i;
    }

    int root(int a) {
        if(parent[a] == a) return a;
        return (parent[a] = root(parent[a]));
    }

    void join(int a, int b) {
        int ra = root(a), rb = root(b);
        if(ra == rb) return;
        parent[ra] = rb;
    }

    bool connected(int a, int b) {
        return root(a) == root(b);
    }

};

int n, m, k, q, parent[MAXN], disToParent[MAXN], grassType[MAXK];
vector<tuple<int, int, int>> edges;
vector<pii> mst[MAXN];
unordered_map<int, set<pii>> treeMap[MAXN];
set<pii> allEdges;

void rootMST(int node, int par) {
    parent[node] = par;
    for(const pii e : mst[node]) {
        if(e.S == par) continue;
        disToParent[e.S] = e.F;
        rootMST(e.S, node);
        if(!treeMap[node].count(grassType[e.S])) treeMap[node].insert(MP(grassType[e.S], set<pii>()));
        treeMap[node][grassType[e.S]].insert(e);
    }
    for(const pair<int, set<pii>> p : treeMap[node]) {
        if(p.F != grassType[node])
            allEdges.insert(*(p.S.begin()));
    }
}

int main() {
    ifstream fin("grass.in");
    ofstream fout("grass.out");
    fin >> n >> m >> k >> q;
    F0R(i, m) {
        int a, b, l;
        fin >> a >> b >> l;
        edges.PB(MT(l, a - 1, b - 1));
    }
    F0R(i, n) {
        fin >> grassType[i];
        grassType[i]--;
    }

    sort(edges.begin(), edges.end());
    DSU dsu(n);
    F0R(i, m) {
        int a = get<1>(edges[i]), b = get<2>(edges[i]), l = get<0>(edges[i]);
        if(!dsu.connected(a, b)) {
            dsu.join(a, b);
            mst[a].PB(MP(l, b));
            mst[b].PB(MP(l, a));
        }
    }

    rootMST(0, -1);

    F0R(query, q) {
        int node, g;
        fin >> node >> g;
        node--, g--;
        if(grassType[node] != g) {
            if(node != 0) {
                allEdges.erase(*(treeMap[parent[node]][grassType[node]].begin()));
                treeMap[parent[node]][grassType[node]].erase(MP(disToParent[node], node));
                if(grassType[node] != grassType[parent[node]] && !treeMap[parent[node]][grassType[node]].empty()) allEdges.insert(*(treeMap[parent[node]][grassType[node]].begin()));

                if(!treeMap[parent[node]].count(g)) treeMap[parent[node]].insert(MP(g, set<pii>()));
                if(!treeMap[parent[node]][g].empty()) allEdges.erase(*(treeMap[parent[node]][g].begin()));
                treeMap[parent[node]][g].insert(MP(disToParent[node], node));
                if(g != grassType[parent[node]]) allEdges.insert(*(treeMap[parent[node]][g].begin()));
            }
            if(treeMap[node].count(g) && !treeMap[node][g].empty()) allEdges.erase(*(treeMap[node][g].begin()));
            if(treeMap[node].count(grassType[node]) && !treeMap[node][grassType[node]].empty()) allEdges.insert(*(treeMap[node][grassType[node]].begin()));
            grassType[node] = g;
        }
        fout << (*allEdges.begin()).F << "\n";
    }
    return 0;
}
