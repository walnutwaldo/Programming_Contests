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
#define MAXN 200000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ll> point;

int n, sizeAt[MAXN];
unordered_set<int> connections[MAXN];
vi centroids;
bool isCentroid[MAXN];
vector<tuple<int, int, int>> transformations;

void dfsSize(int node, int par) {
    sizeAt[node] = 1;
    for(const int next : connections[node]) {
        if(next == par) continue;
        dfsSize(next, node);
        sizeAt[node] += sizeAt[next];
    }
}

void findCentroids(int node, int par) {
    for(const int next : connections[node]) {
        if(next != par && 2 * sizeAt[next] > n) {
            findCentroids(next, node);
            return;
        }
        if(next != par && 2 * sizeAt[next] == n) findCentroids(next, node);
    }
    isCentroid[node] = true;
    centroids.PB(node);
}

void trans(int x, int y, int z) {
    if(y == z) return;
    connections[x].erase(y);
    connections[y].erase(x);
    connections[x].insert(z);
    connections[z].insert(x);
    transformations.PB(MT(x, y, z));
}

pii straighten(int node, int par) {
    int head = node, tail = node;
    vi toProcess;
    for(const int next : connections[node]) if(next != par) toProcess.PB(next);
    for(const int next : toProcess) {
        pii ht = straighten(next, node);
        if(head == node) {
            trans(par, node, ht.S);
            head = ht.S;
            tail = ht.F;
        } else {
            trans(tail, node, ht.S);
            tail = ht.F;
        }
    }
    tail = node;
    return MP(head, tail);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    F0R(i, n - 1) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        connections[a].insert(b);
        connections[b].insert(a);
    }
    dfsSize(0, -1);
    findCentroids(0, - 1);
    for(const int centroid : centroids) {
        vi childrenToProcess;
        for(const int child : connections[centroid]) {
            if(isCentroid[child]) continue;
            childrenToProcess.PB(child);
        }
        for(const int child : childrenToProcess) {
            pii ht = straighten(child, centroid);
            int curr = ht.S;
            int last = -1;
            while(1) {
                if(curr != ht.S) trans(curr, last, ht.S);
                if(curr == centroid) break;
                for(const int next : connections[curr]) {
                    if(next != ht.S) {
                        last = curr;
                        curr = next;
                        break;
                    }
                }
            }
        }
    }
    cout << transformations.size() << "\n";
    for(const tuple<int, int, int> t: transformations) cout << get<0>(t) + 1 << " " << get<1>(t) + 1 << " " << get<2>(t) + 1 << "\n";
    return 0;
}
