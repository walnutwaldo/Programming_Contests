#include <bits/stdc++.h>

using namespace std;

int n, m, t;
long long res[500 * 500];
long long elevation[500][500];

struct DSU {
    
    int sz;
    vector<int> subsize;
    vector<int> par;
    vector<vector<int>> children;
    
    DSU(int sz) : sz(sz), subsize(sz, 1), par(sz, -1), children(sz, vector<int>()) {}
    
    int root(int idx) {
        if (par[idx] == -1) { return idx; }
        return root(par[idx]);
    }
    
    void join(int a, int b) {
        int r1 = root(a), r2 = root(b);
        if (r1 == r2) { return; }
        if (subsize[r1] > subsize[r2]) {
            swap(r1, r2);
        }
        par[r1] = r2;
        children[r2].push_back(r1);
        subsize[r2] += subsize[r1];
    }
    
    bool connected(int a, int b) {
        return root(a) == root(b);
    }
    
    int numIn(int a) {
        return subsize[root(a)];
    }
    
    void fill(int r, long long x) {
        res[r] = x;
        for (const int next : children[r]) { fill(next, x); }
    }
    
};

int compressIdx(int i, int j) {
    return i * m + j;
}

int main() {
    ifstream cin("skilevel.in");
    ofstream cout("skilevel.out");
    cin >> n >> m >> t;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> elevation[i][j];
        }
    }
    vector<pair<long long, pair<int, int>>> v;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i) {
                v.emplace_back(abs(elevation[i][j] - elevation[i - 1][j]),
                               make_pair(compressIdx(i, j), compressIdx(i - 1, j)));
            }
            if (j) {
                v.emplace_back(abs(elevation[i][j - 1] - elevation[i][j]),
                               make_pair(compressIdx(i, j), compressIdx(i, j - 1)));
            }
        }
    }
    sort(v.begin(), v.end());
    DSU dsu(n * m);
    
    for (const pair<long long, pair<int, int>> p : v) {
        int a = p.second.first;
        int b = p.second.second;
        if (!dsu.connected(a, b)) {
            if (dsu.numIn(a) < t && dsu.numIn(a) + dsu.numIn(b) >= t) {
                dsu.fill(dsu.root(a), p.first);
            }
            if (dsu.numIn(b) < t && dsu.numIn(a) + dsu.numIn(b) >= t) {
                dsu.fill(dsu.root(b), p.first);
            }
            dsu.join(a, b);
        }
    }
    
    long long ret = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int c;
            cin >> c;
            if (c) { ret += res[compressIdx(i, j)]; }
        }
    }
    cout << ret << endl;
    return 0;
}
