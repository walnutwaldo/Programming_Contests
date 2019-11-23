#include <bits/stdc++.h>

using namespace std;

int n, m;
char grid[100][100]; // 'R', 'S', or ' '
bool used[100][100];
int largestBlock[2][100][100];
int dp[100][100];

void calcLargest(int x, char c) {
    int up[n][m];
    int left[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            up[i][j] = (grid[i][j] == c || grid[i][j] == ' ');
            if (i && up[i][j]) { up[i][j] += up[i - 1][j]; }
            left[i][j] = (grid[i][j] == c || grid[i][j] == ' ');
            if (j && left[i][j]) { left[i][j] += left[i][j - 1]; }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            largestBlock[x][i][j] = 0;
            if (grid[i][j] == c || grid[i][j] == ' ') {
                largestBlock[x][i][j] = 1;
                if (i && j) {
                    largestBlock[x][i][j] += largestBlock[x][i - 1][j - 1];
                    largestBlock[x][i][j] = min(largestBlock[x][i][j], left[i][j]);
                    largestBlock[x][i][j] = min(largestBlock[x][i][j], up[i][j]);
                }
            }
        }
    }
}

bool stuffin(int i, int j, int l) {
    int amt = dp[i][j];
    if (i - l >= 0) { amt -= dp[i - l][j]; }
    if (j - l >= 0) { amt -= dp[i][j - l]; }
    if (i - l >= 0 && j - l >= 0) { amt += dp[i - l][j - l]; }
    return amt > 0;
}

int main() {
    ifstream cin("skicourse.in");
    ofstream cout("skicourse.out");
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    int res = min(n, m);
    while (true) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                dp[i][j] = (grid[i][j] != ' ');
                if (i) { dp[i][j] += dp[i - 1][j]; }
                if (j) { dp[i][j] += dp[i][j - 1]; }
                if (i && j) { dp[i][j] -= dp[i - 1][j - 1]; }
            }
        }
        pair<int, int> maxPos = { 0, 0 };
        int tobeat = 0;
        calcLargest(0, 'R');
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (largestBlock[0][i][j] > tobeat && stuffin(i, j, largestBlock[0][i][j])) {
                    maxPos = { i, j };
                    tobeat = largestBlock[0][i][j];
                }
            }
        }
        calcLargest(1, 'S');
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (largestBlock[1][i][j] > tobeat && stuffin(i, j, largestBlock[1][i][j])) {
                    maxPos = { i, j };
                    tobeat = largestBlock[1][i][j];
                }
            }
        }
        res = min(res, tobeat);
        for (int i = maxPos.first; i > maxPos.first - tobeat; i--) {
            for (int j = maxPos.second; j > maxPos.second - tobeat; j--) {
                grid[i][j] = ' ';
            }
        }
        used[maxPos.first][maxPos.second] = 1;
        bool cont = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] != ' ') { cont = true; } }
        }
        if (!cont) { break; }
    }
    cout << res << endl;
    return 0;
}
