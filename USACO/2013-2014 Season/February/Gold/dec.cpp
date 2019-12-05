#include <bits/stdc++.h>

using namespace std;

int n, b;
int dp[1 << 20];
int skill[20][20];
vector<pair<int, int>> bonuses[21];

inline void upd(int& a, int b) { a = max(a, b); }

int main() {
    ifstream cin("dec.in");
    ofstream cout("dec.out");
    cin >> n >> b;
    for (int i = 0; i < b; i++) {
        int k, p, a;
        cin >> k >> p >> a;
        bonuses[k].emplace_back(p, a);
    }
    for (int i = 0; i < n; i++) {
        sort(bonuses[i].begin(), bonuses[i].end());
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> skill[i][j];
        }
    }
    dp[0] = 0;
    for (int i = 0; i < (1 << n); i++) {
        int numCows = __builtin_popcount(i);
        for (int j = 0; j < bonuses[numCows].size(); j++) {
            if (dp[i] >= bonuses[numCows][j].first) {
                dp[i] += bonuses[numCows][j].second;
            }
        }
        for (int j = 0; j < n; j++) {
            if (!((i >> j) & 1)) {
                upd(dp[i | (1 << j)], dp[i] + skill[j][numCows]);
            }
        }
    }
    cout << dp[(1 << n) - 1] << endl;
    return 0;
}
