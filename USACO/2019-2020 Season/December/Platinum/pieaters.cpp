#include <bits/stdc++.h>

using namespace std;

struct cow {
    int l, r;
    long long w;
    
    bool operator<(const cow& other) const {
        return make_tuple(l, r, w) > make_tuple(other.l, other.r, other.w);
    }
    
};

int n, m;
vector<cow> cows;
long long dp[300][300];

long long getDP(int l, int r) {
    if (r < l) { return 0; }
    return dp[l][r];
}

int main() {
    ifstream cin("pieaters.in");
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        long long w;
        int l, r;
        cin >> w >> l >> r;
        l--, r--;
        cows.push_back((cow){ l, r, w });
    }
    for (int rightEnd = 0; rightEnd < n; rightEnd++) {
        for (int leftEnd = rightEnd; leftEnd >= 0; leftEnd--) {
            for (const cow& c : cows) {
                if (c.l >= leftEnd && c.r <= rightEnd) {
                    for (int i = c.l; i <= c.r; i++) {
                        dp[leftEnd][rightEnd] = max(dp[leftEnd][rightEnd], getDP(leftEnd, i - 1) + getDP(i + 1, rightEnd) + c.w);
                    }
                }
            }
            cout << leftEnd << " " << rightEnd << " " << dp[leftEnd][rightEnd] << endl;
        }
    }
}
