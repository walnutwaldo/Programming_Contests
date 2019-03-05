#include <bits/stdc++.h>

#define F0R(i, a) for (int i = 0; i < a; i++)

#define PB push_back

using namespace std;

typedef vector<int> vi;

struct BIT {
    
    int sz;
    int *tree;
    
    BIT(int _sz) : sz(_sz) {tree = new int[sz + 1]();}
    
    void update(int idx, int v) {for (idx++; idx <= sz; idx += idx & -idx) tree[idx] ^= v; }
    
    int query(int idx) {
        int res = 0;
        for (idx++; idx; idx -= idx & -idx) res ^= tree[idx];
        return res;
    }
    
    int query(int lo, int hi) {return query(hi) ^ query(lo - 1);}
    
};

#define MAXN 200000

int n, q, e[MAXN];
vi adj[MAXN];

vi cHead, cLen, cDepth;
vector<BIT> cbit;
int chain[MAXN], cIdx[MAXN], par[MAXN], subsize[MAXN];

int getSubSize(int node, int par) {
    if (subsize[node] != 0) return subsize[node];
    subsize[node] = 1;
    for (const int next : adj[node]) if (next != par) subsize[node] += getSubSize(next, node);
    return subsize[node];
}

void buildHLD(int node, int _par) {
    par[node] = _par;
    if (_par == -1 || chain[_par] != chain[node]) {
        cHead.PB(node);
        cLen.PB(0);
        cDepth.PB((_par == -1) ? 0 : cDepth[chain[_par]] + 1);
    } else cIdx[node] = cIdx[_par] + 1;
    cLen[chain[node]]++;

    int mxNext = -1;
    for (const int next : adj[node]) if (next != _par && (mxNext == -1 || getSubSize(next, node) > getSubSize(mxNext, node))) mxNext = next;
    
    if (mxNext == -1) {
    	assert((int)cbit.size() == chain[node]);
    	cbit.PB(BIT(cLen[chain[node]]));
    } else {
        chain[mxNext] = chain[node];
        buildHLD(mxNext, node);
    }
    for (const int next : adj[node]) if (next != _par && next != mxNext) {
            chain[next] = cHead.size();
            buildHLD(next, node);
        }
    cbit[chain[node]].update(cIdx[node], e[node]);
}

void update(int node, int v) {
    cbit[chain[node]].update(cIdx[node], v ^ e[node]);
    e[node] = v;
}

int query(int node1, int node2) {
    int res = 0;
    while (chain[node1] != chain[node2]) {
        if (cDepth[chain[node1]] >= cDepth[chain[node2]]) {
            res ^= cbit[chain[node1]].query(0, cIdx[node1]);
            node1 = par[cHead[chain[node1]]];
        } else {
            res ^= cbit[chain[node2]].query(0, cIdx[node2]);
            node2 = par[cHead[chain[node2]]];
        }
    }
    res ^= cbit[chain[node1]].query(min(cIdx[node1], cIdx[node2]), max(cIdx[node1], cIdx[node2]));
    return res;
}

int main() {
    ifstream cin("cowland.in");
    ofstream cout("cowland.out");
    cin >> n >> q;
    F0R(i, n) cin >> e[i];
    F0R(i, n - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].PB(v);
        adj[v].PB(u);
    }
    buildHLD(0, -1);
    F0R(i, q) {
        int t;
        cin >> t;
        if (t == 1) {
            int node, v;
            cin >> node >> v;
            node--;
            update(node, v);
        } else {
            int node1, node2;
            cin >> node1 >> node2;
            node1--, node2--;
            cout << query(node1, node2) << "\n";
        }
    }
    return 0;
}
