#include <bits/stdc++.h>

using namespace std;

int n, m[100000];
long double total;
long double pref[100000], dp[100000];

bool possible(long double prod) {
    pref[0] = m[0] - prod;
    for (int i = 1; i < n - 1; i++) { pref[i] = m[i] - prod + pref[i - 1]; }
    long double minpref = pref[0];
    for (int i = 1; i < n - 1; i++) {
        if (pref[i] - minpref >= total - prod * n) { return true; }
        minpref = min(minpref, pref[i]);
    }
    return false;
}

int main() {
    ifstream cin("sabotage.in");
    ofstream cout("sabotage.out");
    cin >> n;
    for (int i = 0; i < n; i++) { cin >> m[i]; total += m[i]; }
    long double lo = 0, hi = (1 << 14);
    while (round(lo * 1000) != round(hi * 1000)) {
        long double mid = (lo + hi) / 2;
        if (possible(mid)) { hi = mid; } else { lo = mid; }
    }
    cout << fixed << setprecision(3) << lo << endl;
    return 0;
}
