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
#define MAXN 100000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int q, n, centroidParent[MAXN], centroidDepth[MAXN], inSubtree[MAXN];
vi connections[MAXN], disToCentroidParent[MAXN];
pair<pii, pii> farthestCentroidChild[MAXN];
pair<char, int> queries[MAXN];
bool on[MAXN];

void addChildHeight(int node, int h, int group) {
    if(h > farthestCentroidChild[node].F.F) {
        if(farthestCentroidChild[node].F.S != group)
            swap(farthestCentroidChild[node].F, farthestCentroidChild[node].S);
        farthestCentroidChild[node].F.F = h;
        farthestCentroidChild[node].F.S = group;
    } else if(h > farthestCentroidChild[node].S.F && farthestCentroidChild[node].F.S != group) {
        farthestCentroidChild[node].S.F = h;
        farthestCentroidChild[node].S.S = group;
    }
}

int farCentroidChildOther(int node, int group) {
    if(farthestCentroidChild[node].F.S == group)
        return farthestCentroidChild[node].S.F;
    return farthestCentroidChild[node].F.F;
}

void dfsSubtreeSize(int node, int par) {
    inSubtree[node] = 1;
    for(const int next : connections[node])
        if(centroidParent[next] == -2 && next != par) {
            dfsSubtreeSize(next, node);
            inSubtree[node] += inSubtree[next];
        }
}

int dfsCentroid(int node, int par, int treeSize) {
    for(const int next : connections[node])
        if(centroidParent[next] == -2 && next != par && inSubtree[next] > treeSize / 2)
            return dfsCentroid(next, node, treeSize);
    return node;
}

void dfsCentroidDis(int node, int par, int dis) {
    disToCentroidParent[node].PB(dis);
    for(const int next : connections[node])
        if(centroidParent[next] == -2 && next != par)
            dfsCentroidDis(next, node, dis + 1);
}

void findCentroid(int node, int par, int depth) {
    dfsSubtreeSize(node, -1);
    int centroid = dfsCentroid(node, -1, inSubtree[node]);
    dfsCentroidDis(centroid, -1, 0);
    centroidParent[centroid] = par;
    centroidDepth[centroid] = depth;
    for(const int next : connections[centroid])
        if(centroidParent[next] == -2)
            findCentroid(next, centroid, depth + 1);
}

int main() {
    ifstream fin("newbarn.in");
    ofstream fout("newbarn.out");
    fin >> q;
    F0R(i, q) {
        char comm;
        int k;
        fin >> comm >> k;
        k--;
        queries[i] = MP(comm, k);
        if(queries[i].F == 'B') {
            if(queries[i].S != -2) {
                connections[n].PB(k);
                connections[k].PB(n);
            }
            n++;
        }
    }
    F0R(i, n) centroidParent[i] = -2;
    F0R(i, n) if(centroidParent[i] == -2)
        findCentroid(i, -1, 0);
    F0R(i, n) farthestCentroidChild[i] = MP(MP(INT_MIN, -1), MP(INT_MIN, -2));
    int numNodes = 0;
    F0R(i, q) {
        if(queries[i].F == 'B') {
            int curr = numNodes;
            int last = -3;
            R0F(j, centroidDepth[numNodes] + 1) {
                addChildHeight(curr, disToCentroidParent[numNodes][j], last);
                last = curr;
                curr = centroidParent[curr];
            }
            on[numNodes] = 1;
            numNodes++;
        } else {
            int node = queries[i].S;
            int curr = node, last = -4;
            int res = 0;
            R0F(j, centroidDepth[node] + 1) {
                if(on[curr])
                    res = max(res, disToCentroidParent[node][j] + farCentroidChildOther(curr, last));
                last = curr;
                curr = centroidParent[curr];
            }
            fout << res << "\n";
        }
    }
    return 0;
}
