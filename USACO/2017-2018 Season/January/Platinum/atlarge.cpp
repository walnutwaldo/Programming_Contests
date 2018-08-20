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
#define R real()
#define I image()
#define PI acos(-1)
#define MAXN 70000

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;
typedef complex<ld> cld;

struct RUSQ {

    int sz;
    ll *tree;

    RUSQ(int sz) {
        this->sz = sz;
        tree = new ll[sz + 1];
        memset(tree, 0, (sz + 1) * sizeof(ll));
    }

    void update(int idx, ll v) {
        for(idx++; idx <= sz; idx += (idx & -idx)) tree[idx] += v;
    }

    void updateRange(int lo, int hi, int v) {
        update(lo, v);
        update(hi + 1, -v);
    }

    ll query(int idx) {
        ll total = 0;
        for(idx++; idx > 0; idx -= (idx & -idx)) total += tree[idx];
        return total;
    }

    void reset() {
        memset(tree, 0, (sz + 1) * sizeof(ll));
    }
};

struct MergeSortTree {

    int s, e, *arr, *lPos, *rPos;
    RUSQ *val;
    MergeSortTree *lChild = NULL, *rChild = NULL;

    MergeSortTree(int sz, int* a) {
        s = 0, e = sz;
        buildTree(a);
    }

    MergeSortTree(int ss, int ee, int* a) {
        s = ss, e = ee;
        buildTree(a);
    }

    void buildTree(int* a) {
        val = new RUSQ(e - s);
        if(e == s + 1) arr = new int[1] {a[s]};
        else {
            int mid = (s + e) >> 1;
            lChild = new MergeSortTree(s, mid, a);
            rChild = new MergeSortTree(mid, e, a);
            arr = new int[e - s], lPos = new int[mid - s], rPos = new int[e - mid];
            int i = 0, j = 0;
            while(i < mid - s || j < e - mid) {
                if(i == mid - s || j < e - mid && rChild->arr[j] < lChild->arr[i]) {
                    rPos[j] = i + j;
                    arr[i + j] = rChild->arr[j++];
                } else {
                    lPos[i] = i + j;
                    arr[i + j] = lChild->arr[i++];
                }
            }
        }
    }

    void update(int lo, int hi, int cap, int inc) {
        if(hi <= s || lo >= e) return;
        if(s >= lo && e <= hi) {
            int pos = UB(arr, arr + e - s, cap) - arr;
            if(pos > 0) val->updateRange(0, pos - 1, inc);
        } else {
            lChild->update(lo, hi, cap, inc);
            rChild->update(lo, hi, cap, inc);
        }
    }

    int query(int i) {
        return valAndPos(i).F;
    }

    pii valAndPos(int i) {
        if(s == i && e == i + 1) return MP(val->query(0), 0);
        else {
            int mid = (s + e) >> 1;
            pii res;
            if(i < mid) {
                res = lChild->valAndPos(i);
                res.S = lPos[res.S];
            } else {
                res = rChild->valAndPos(i);
                res.S = rPos[res.S];
            }
            res.F += val->query(res.S);
            return res;
        }
    }

};

int n, depth[MAXN], parent[MAXN], closestExit[MAXN], disFromNearestExit[MAXN];
pii t[MAXN];
vi q, connections[MAXN];
MergeSortTree *tree;

void rootTree(int node, int currT) {
    t[node].F = currT++;
    for(const int next : connections[node]) if(next != parent[node]) {
            parent[next] = node;
            depth[currT] = depth[t[node].F] + 1;
            rootTree(next, currT);
            currT = t[next].S;
        }
    t[node].S = currT;
}

void update(int node, int lastNode, int dis) {
    if(dis < 0 || node == -1) return;
    tree->update(t[node].F, t[node].S, depth[t[node].F] + dis, 1);
    if(lastNode != parent[node]) {
        tree->update(t[lastNode].F, t[lastNode].S, depth[t[node].F] + dis, - 1);
        update(parent[node], node, dis - 1);
    }
}

int main() {
    ifstream fin("atlarge.in");
    ofstream fout("atlarge.out");
    fin >> n;
    F0R(i, n - 1) {
        int a, b;
        fin >> a >> b;
        a--, b--;
        connections[a].PB(b);
        connections[b].PB(a);
    }
    parent[0] = -1;
    rootTree(0, 0);
    tree = new MergeSortTree(n, depth);
    tree->update(0, n, n, 1);
    F0R(i, n) if(connections[i].size() == 1) {
        closestExit[i] = i;
        q.PB(i);
    } else closestExit[i] = -1;
    F0R(i, n) {
        int node = q[i];
        for(const int next : connections[node]) if(closestExit[next] == -1) {
                closestExit[next] = closestExit[node];
                disFromNearestExit[next] = disFromNearestExit[node] + 1;
                q.PB(next);
            }
    }
    F0R(node, n) for(const int next : connections[node]) if(closestExit[next] != closestExit[node]) update(next, node, disFromNearestExit[next] - 1);
    F0R(i, n) fout << tree->query(t[i].F) << "\n";
    return 0;
}
