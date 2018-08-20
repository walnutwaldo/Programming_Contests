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

int n, inSubtree[MAXN], parent[MAXN], nameLength[MAXN];
vi children[MAXN];
ll disToLeavesInSubtree[MAXN], totalDis[MAXN], minTotalDis = (1LL << 63) - 1;

void dfsTotalDis(int node) {
    if(node == 0)
        totalDis[node] = disToLeavesInSubtree[node];
    else
        totalDis[node] = totalDis[parent[node]] - inSubtree[node] * (nameLength[node] + 1) + (inSubtree[0] - inSubtree[node]) * 3;
    minTotalDis = min(minTotalDis, totalDis[node]);
    for(const int child : children[node])
        dfsTotalDis(child);
}

void dfsSubtreeDis(int node) {
    if(children[node].empty())
        return;
    for(const int child: children[node]) {
        dfsSubtreeDis(child);
        disToLeavesInSubtree[node] += disToLeavesInSubtree[child] + inSubtree[child] * (nameLength[child] + 1);
    }
}

void dfsSubtree(int node) {
    if(children[node].empty())
        inSubtree[node] = 1;
    for(const int child : children[node]) {
        dfsSubtree(child);
        inSubtree[node] += inSubtree[child];
    }
}

int main() {
    ifstream fin("dirtraverse.in");
    ofstream fout("dirtraverse.out");
    fin >> n;
    F0R(i, n) {
        string name;
        fin >> name;
        nameLength[i] = name.size();
        int m;
        fin >> m;
        F0R(j, m) {
            int child;
            fin >> child;
            child--;
            children[i].PB(child);
            parent[child] = i;
        }
    }
    dfsSubtree(0);
    dfsSubtreeDis(0);
    dfsTotalDis(0);
    fout << minTotalDis - inSubtree[0] << "\n";
    return 0;
}
