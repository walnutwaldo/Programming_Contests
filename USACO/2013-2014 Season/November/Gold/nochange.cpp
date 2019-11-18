#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int k, n;
long long v[16];
long long c[100000];
int dp[1 << 16];

void upd(int& a, int b) { a = max(a, b); }

int main() {
    ifstream cin("nochange.in");
    ofstream cout("nochange.out");
    cin >> k >> n;
    for (int i = 0; i < k; i++) {
        cin >> v[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        if (i) { c[i] += c[i - 1]; }
    }
    for (int i = 0; i < (1 << k); i++) { dp[i] = 0; }
    long long res = -1;
    for (int popcount = k; popcount >= 0; popcount--) {
        for (int mask = 0; mask < (1 << k); mask++) {
            if (__builtin_popcount(mask) == popcount) {
                long long base = dp[mask] ? c[dp[mask] - 1] : 0;
                long long curr = 0;
                for (int i = 0; i < k; i++) {
                    if ((mask >> i) & 1) {
                        curr += v[i];
                        upd(dp[mask ^ (1 << i)], (int)(upper_bound(c, c + n, base + v[i]) - c));
                    }
                }
                if (dp[mask] == n) { res = max(res, curr); }
            }
        }
    }
    cout << res << endl;
}
