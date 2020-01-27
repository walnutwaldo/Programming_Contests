#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000
#define MOD 1000000007

int par[MAXN * MAXN], sz[MAXN * MAXN];
long long cnt[MAXN * MAXN];

bool grid[MAXN][MAXN];

int n, m;

int root(int x) {
    if (par[x] == x) { return x; }
    return par[x] = root(par[x]);
}

void join(int i, int j) {
    int r1 = root(i), r2 = root(j);
    if (r1 == r2) { return; }
    if (sz[r1] < sz[r2]) { swap(r1, r2); }
    par[r2] = r1;
    cnt[r1] = (cnt[r1] * cnt[r2]) % MOD;
    sz[r1] += (sz[r1] == sz[r2]);
}

void join(int r1, int c1, int r2, int c2) {
    join(r1 * m + c1, r2 * m + c2);
}

int main() {
    ifstream fin("cave.in");
    ofstream fout("cave.out");
    fin >> n >> m;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            char c;
            fin >> c;
            grid[i][j] = (c == '.');
            cnt[i * m + j] = 1;
            par[i * m + j] = i * m + j;
            sz[i * m + j] = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i > 0 && grid[i][j] && grid[i - 1][j]) {
                join(i, j, i - 1, j);
            }
            if (j > 0 && grid[i][j] && grid[i][j - 1]) {
                join(i, j, i, j - 1);
            }
        }
        set<int> roots;
        for (int j = 0; j < m; j++) { if (grid[i][j]) { roots.insert(root(i * m + j)); } }
        for (const int j : roots) { cnt[j] = (cnt[j] + 1) % MOD; }
    }
    long long res = 1;
    for (int i = 0; i < n * m; i++) { if (par[i] == i) { res = (res * cnt[i]) % MOD; } }
    fout << res << endl;
}
