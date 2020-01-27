#include <bits/stdc++.h>

#define MAXN 50000

using namespace std;

typedef long long ll;

#define MOD 1000000007
#define NEGHALF 500000003

int n, k, q, a[MAXN];
array<ll, 20> invPref[MAXN], pref[MAXN];
array<array<ll, 20>, 20> invRunning, running;

void madd(ll& a, ll b) { a = (a + b) % MOD; }

int main() {
    ifstream fin("nondec.in");
    ofstream fout("nondec.out");
    fin >> n >> k;
    for (int i = 0; i < n; i++) {
        fin >> a[i];
        a[i]--;
    }
    for (int i = 0; i < k; i++) {
        invRunning[i][i] = running[i][i] = 1;
    }
    for (int i = 0; i < n; i++) {
        for (int r = 0; r < k; r++) {
            ll toAdd = 0;
            for (int c = 0; c <= a[i]; c++) {
                madd(toAdd, running[r][c]);
            }
            madd(running[r][a[i]], toAdd);
        }
        for (int r = 0; r <= a[i]; r++) {
            for (int c = 0; c < k; c++) {
                madd(invRunning[r][c], (NEGHALF * invRunning[a[i]][c]) % MOD);
            }
        }
        for (int j = 0; j < k; j++) { invPref[i][j] = invRunning[0][j]; }
        for (int r = 0; r < k; r++) {
            pref[i][r] = 0;
            for (int c = 0; c < k; c++) {
                madd(pref[i][r], running[r][c]);
            }
        }
    }
    fin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        fin >> l >> r;
        l--, r--;
        if (l == 0) {
            fout << pref[r][0] << "\n";
        } else {
            ll res = 0;
            for (int j = 0; j < k; j++) {
                madd(res, invPref[l - 1][j] * pref[r][j] % MOD);
            }
            fout << res << "\n";
        }
    }
}
