#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define ran() (rand() & 0x7FFF)
#define rand31() ((ran() << 16) | (ran() << 1) | (ran() & 1))
#define rand32() ((ran() << 17) | (ran() << 2) | (ran() & 3))
#define rand63() (((ll)ran() << 48) | ((ll)ran() << 33) | ((ll)ran() << 18) | ((ll)ran() << 3) | ((ll)ran() & 7))
#define rand64() (((ll)ran() << 49) | ((ll)ran() << 34) | ((ll)ran() << 19) | ((ll)ran() << 4) | ((ll)ran() & 15))

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define X real()
#define Y imag()
#define MAXN 50000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n, m, subSize[MAXN];
ll res[MAXN - 1];
pii parent[MAXN];
vector<pii> connections[MAXN], children[MAXN];
vector<vi> addAt[MAXN], removeAt[MAXN];
vi edgeAt[MAXN];
map<int, int> mp;

int numChains = 0, chainHead[MAXN], chainPos[MAXN], chainID[MAXN], chainSize[MAXN], chainDepth[MAXN];

void hld(int node) {
    chainID[node] = numChains;
    chainPos[node] = chainSize[numChains];
    chainSize[numChains]++;
    addAt[numChains].PB(vi());
    removeAt[numChains].PB(vi());
    edgeAt[numChains].PB(parent[node].S);

    int bestChild = -1;
    for(const pii p : children[node])
        if(bestChild == -1 || subSize[p.F] > subSize[bestChild])
            bestChild = p.F;
    if(bestChild != -1)
        hld(bestChild);
    for(const pii p : children[node])
        if(p.F != bestChild) {
            chainHead[++numChains] = p.F;
            chainDepth[numChains] = chainDepth[chainID[node]] + 1;
            hld(p.F);
        }
}


void root(int node) {
    subSize[node] = 1;
    for(const pii p : connections[node])
        if(p.F != parent[node].F) {
            children[node].PB(p);
            parent[p.F] = MP(node, p.S);
            root(p.F);
            subSize[node] += subSize[p.F];
        }
}

void addPath(int p, int q, ll r) {
    while(chainID[p] != chainID[q]) {
        if(chainDepth[chainID[p]] >= chainDepth[chainID[q]]) {
            addAt[chainID[p]][0].PB(r);
            removeAt[chainID[p]][chainPos[p]].PB(r);
            int edge = parent[chainHead[chainID[p]]].S;
            p = parent[chainHead[chainID[p]]].F;
            res[edge] = min(res[edge], r);
        } else {
            addAt[chainID[q]][0].PB(r);
            removeAt[chainID[q]][chainPos[q]].PB(r);
            int edge = parent[chainHead[chainID[q]]].S;
            q = parent[chainHead[chainID[q]]].F;
            res[edge] = min(res[edge], r);
        }
    }
    addAt[chainID[p]][min(chainPos[p], chainPos[q])].PB(r);
    removeAt[chainID[p]][max(chainPos[p], chainPos[q])].PB(r);
}

void workChain(int chain) {
    mp.clear();
    F0R(i, chainSize[chain] - 1) {
        for(const int j : addAt[chain][i]) mp[j]++;
        for(const int j : removeAt[chain][i]) if(--mp[j] == 0) mp.erase(j);
        if(!mp.empty()) res[edgeAt[chain][i + 1]] = (*mp.begin()).F;
    }
}

int main() {
    ifstream fin("disrupt.in");
    ofstream fout("disrupt.out");
    fin >> n >> m;
    F0R(i, n - 1) {
        int p, q;
        fin >> p >> q;
        p--, q--;
        connections[p].PB(MP(q, i));
        connections[q].PB(MP(p, i));
        res[i] = (1LL << 63) - 1;
    }
    parent[0] = MP(-1, -1);
    root(0);
    hld(0);
    numChains++;
    F0R(i, m) {
        int p, q, r;
        fin >> p >> q >> r;
        p--, q--;
        addPath(p, q, r);
    }
    F0R(i, numChains) workChain(i);
    F0R(i, n - 1) {
        if(res[i] != (1LL << 63) - 1) fout << res[i] << "\n";
        else fout << "-1\n";
    }
    return 0;
}
