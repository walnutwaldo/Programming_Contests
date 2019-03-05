int n, q;
vi adj[MAXN];

vi cHead, cLen, cDepth;
vector<STRUCT> cstruct; // replace STRUCT with whatever data struct you are using
int chain[MAXN], cIdx[MAXN], par[MAXN], subsize[MAXN];

int getSubSize(int node, int par) {
    if (subsize[node] != 0) return subsize[node];
    subsize[node] = 1;
    for (const int next : adj[node]) if (next != par) subsize[node] += getSubSize(next, node);
    return subsize[node];
}

// rewrite depending on situtation
void initStruct(STRUCT& s, int node) {}

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
    
    if (mxNext == -1) cstruct.PB(STRUCT(cLen[chain[node]]));
    else {
        chain[mxNext] = chain[node];
        buildHLD(mxNext, node);
    }
    for (const int next : adj[node]) if (next != _par && next != mxNext) {
            chain[next] = cHead.size();
            buildHLD(next, node);
        }
  	initStruct(cstruct[chain[node]], node);
}

void update(int node, int v) {}

// rewrite depending on situation
void comb(int& res, int v) { res ^= v; }

// combines node values NOT edge values
// may need to rewrite depending on situation
// uses inclusive upper bounds (may need to change)
int query(int node1, int node2) {
    int res = 0;
    while (chain[node1] != chain[node2]) {
        if (cDepth[chain[node1]] >= cDepth[chain[node2]]) {
            comb(res, cstruct[chain[node1]].query(0, cIdx[node1])); 
            node1 = par[cHead[chain[node1]]];
        } else {
            comb(res, cstruct[chain[node2]].query(0, cIdx[node2]));
            node2 = par[cHead[chain[node2]]];
        }
    }
    comb(res, cstruct[chain[node1]].query(min(cIdx[node1], cIdx[node2]), max(cIdx[node1], cIdx[node2])));
    return res;
}
