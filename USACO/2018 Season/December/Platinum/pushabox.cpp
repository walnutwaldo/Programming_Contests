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
#define MAXN 1500

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct BCC {

    bool *visited;
    int *depth, *lowpoint, numNodes;
    vi *connections;
    vector<vector<pii>> components;

    BCC(int sz) {
        numNodes = sz;
        depth = new int[numNodes];
        lowpoint = new int[numNodes];
        visited = new bool[numNodes];
        connections = new vi[numNodes];
        memset(depth, 0, numNodes);
    }

    void addEdge(int a, int b) {
        connections[a].PB(b);
        connections[b].PB(a);
    }

    void calculateBCCs() {
        memset(visited, 0, numNodes);
        vector<pii> *s = new vector<pii>();
        F0R(i, numNodes) if(!visited[i]) dfs(i, 0, -1, s);
    }

    void dfs(int node, int d, int parent, vector<pii>* s) {
        visited[node] = true;
        depth[node] = lowpoint[node] = d;
        for(const int next : connections[node]) {
            pii edge = MP(min(node, next), max(node, next));
            if(visited[next] && next != parent) {
                lowpoint[node] = min(lowpoint[node], depth[next]);
                if(depth[next] < d) s->PB(edge);
            } else if (!visited[next]) {
                s->PB(edge);
                dfs(next, d + 1, node, s);
                lowpoint[node] = min(lowpoint[node], lowpoint[next]);
                if(lowpoint[next] >= d) {
                    vector<pii> v;
                    while(true) {
                        pii p = s->back();
                        s->pop_back();
                        v.PB(p);
                        if(p == edge) break;
                    }
                    components.PB(v);
                }
            }
        }
    }
};

int n, m, q, compMap[MAXN * MAXN][2], dr[4] { -1, 0, 1, 0}, dc[4] {0, 1, 0, -1};
bool blocked[MAXN][MAXN], visited[MAXN][MAXN], canReach[MAXN][MAXN], canReachSide[MAXN][MAXN][4];
pii block, bessie;
BCC *bcc;

bool available(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < m && !blocked[r][c];
}

int sideMask(int r1, int c1, int r2, int c2) {
    F0R(i, 4) if(r1 + dr[i] == r2 && c1 + dc[i] == c2) return i;
}

bool sideSameComp(int r1, int c1, int r2, int c2, int r3, int c3) {
    if(!available(r2, c2)) return false;
    int square1 = r1 * m + c1;
    int square2 = r2 * m + c2;
    int square3 = r3 * m + c3;
    return compMap[max(square1, square3)][max(square1, square3) - 1 == min(square1, square3)] == compMap[max(square2, square3)][max(square2, square3) - 1 == min(square2, square3)];
}

int getMask(int blockR, int blockC, int bessieR, int bessieC) {
    int mask = 0;
    F0R(i, 4) if(sideSameComp(bessieR, bessieC, blockR + dr[i], blockC + dc[i], blockR, blockC)) mask |= (1 << i);
    return mask;
}

void dfs(int r, int c) {
    visited[r][c] = true;
    F0R(i, 4) if(r + dr[i] == block.F && c + dc[i] == block.S) {
        bessie.F = r, bessie.S = c;
        return;
    }
    F0R(i, 4) if(available(r + dr[i], c + dc[i]) && (r + dr[i] != block.F || c + dc[i] != block.S) && !visited[r + dr[i]][c + dc[i]]) dfs(r + dr[i], c + dc[i]);
}

void work(int blockR, int blockC, int bessieR, int bessieC) {
    if(!available(blockR, blockC) || blocked[blockR][blockC] || canReachSide[blockR][blockC][sideMask(blockR, blockC, bessieR, bessieC)]) return;
    int mask = getMask(blockR, blockC, bessieR, bessieC);
    canReach[blockR][blockC] = true;
    F0R(i, 4) if(mask & (1 << i)) canReachSide[blockR][blockC][i] = true;
    F0R(i, 4) if(mask & (1 << i)) work(blockR - dr[i], blockC - dc[i], blockR, blockC);
}

int main() {
    ifstream fin("pushabox.in");
    ofstream fout("pushabox.out");
    fin >> n >> m >> q;
    bcc = new BCC(n * m);
    F0R(r, n) F0R(c, m) {
        char symb;
        fin >> symb;
        if(symb == '#') blocked[r][c] = true;
        if(symb == 'A') bessie = MP(r, c);
        if(symb == 'B') block = MP(r, c);
    }
    F0R(r, n) F0R(c, m) {
        if(blocked[r][c]) continue;
        F0R(i, 2) if(available(r + dr[i], c - dc[i])) bcc->addEdge(r * m + c, (r + dr[i]) * m + c - dc[i]);
    }
    bcc->calculateBCCs();
    F0R(i, bcc->components.size()) for(const pii p : bcc->components[i]) compMap[p.S][p.S - 1 == p.F] = i;
    dfs(bessie.F, bessie.S);
    if(abs(bessie.F - block.F) + abs(bessie.S - block.S) != 1) canReach[block.F][block.S] = true;
    else work(block.F, block.S, bessie.F, bessie.S);
    F0R(i, q) {
        int r, c;
        fin >> r >> c;
        r--, c--;
        if(canReach[r][c]) fout << "YES\n";
        else fout << "NO\n";
    }
    return 0;
}
