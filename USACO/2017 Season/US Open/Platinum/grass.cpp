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
#define MAXN 200000
#define MAXK 200000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, m, k, q, parent[MAXN], disToParent[MAXN], grassType[MAXK + 1];
priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
vector<pii> mst[MAXN];
unordered_map<int, set<pii>> treeMap[MAXN];
set<pii> allEdges;

int root(int a) {
    if(parent[a] == a) return a;
    return (parent[a] = root(parent[a]));
}

bool join(int a, int b) {
    int ra = root(a), rb = root(b);
    if(ra == rb) return false;
    parent[ra] = rb;
    return true;
}

void dfs(int node, int par) {
    parent[node] = par;
    for(const pii e: mst[node]) {
        if(e.S == par) continue;
        disToParent[e.S] = e.F;
        dfs(e.S, node);
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
    k++;
    F0R(i, m) {
        int a, b, l;
        fin >> a >> b >> l;
        pq.push(MT(l, a - 1, b - 1));
    }
    F0R(i, n) fin >> grassType[i];
    F0R(i, n) parent[i] = i;
    F0R(i, m) {
        tuple<int, int, int> e = pq.top();
        pq.pop();
        int a = get<1>(e), b = get<2>(e), l = get<0>(e);
        if(join(a, b)) {
            mst[a].PB(MP(l, b));
            mst[b].PB(MP(l, a));
        }
    }
    dfs(0, -1);
    F0R(query, q) {
        int node, g;
        fin >> node >> g;
        node--;
        if(grassType[node] != g) {
            if(parent[node] != -1) {
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
