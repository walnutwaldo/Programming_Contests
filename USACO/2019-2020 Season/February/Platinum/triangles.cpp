#include <bits/stdc++.h>

#define PB push_back

using namespace std;

typedef pair<int, int> pii;

int n;
bool grid[600][600];
int xDirCnt[600][600], yDirCnt[600][600];
vector<int> pointsWithX[600];
vector<int> pointsWithY[600];

int countBetween(vector<int>& v, int a, int b) {
    return max(0, (int)(upper_bound(v.begin(), v.end(), b) - lower_bound(v.begin(), v.end(), a)));
}

int main() {
    ifstream cin("triangles.in");
    ofstream cout("triangles.out");
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            if (c == '*') {
                int x = i + j;
                int y = i - j + n - 1;
                pointsWithX[x].PB(y);
                pointsWithY[y].PB(x);
                grid[x][y] = true;
            }
        }
    }
    for (int i = 0; i < 2 * n; i++) {
        for (int idx1 = 0; idx1 < pointsWithX[i].size(); idx1++) {
            for (int idx2 = idx1 + 1; idx2 < pointsWithX[i].size(); idx2++) {
                int y1 = pointsWithX[i][idx1];
                int y2 = pointsWithX[i][idx2];
                if (i - (y2 - y1) >= 0) {
                    yDirCnt[i - (y2 - y1)][y1]++;
                    yDirCnt[i - (y2 - y1)][y2 + 1]--;
                }
                if (i + (y2 - y1) < 2 * n) {
                    yDirCnt[i + (y2 - y1)][y1]++;
                    yDirCnt[i + (y2 - y1)][y2 + 1]--;
                }
            }
        }
        for (int idx1 = 0; idx1 < pointsWithY[i].size(); idx1++) {
            for (int idx2 = idx1 + 1; idx2 < pointsWithY[i].size(); idx2++) {
                int x1 = pointsWithY[i][idx1];
                int x2 = pointsWithY[i][idx2];
                if (x2 > x1 + 1) {
                    if (i - (x2 - x1) >= 0) {
                        xDirCnt[x1 + 1][i - (x2 - x1)]++;
                        xDirCnt[x2][i - (x2 - x1)]--;
                    }
                    if (i + (x2 - x1) < 2 * n) {
                        xDirCnt[x1 + 1][i + (x2 - x1)]++;
                        xDirCnt[x2][i + (x2 - x1)]--;
                    }
                }
            }
        }
    }
    int res = 0;
    for (int x = 0; x < 2 * n; x++) {
        int mult = 0;
        for (int y = 0; y < 2 * n; y++) {
            mult += yDirCnt[x][y];
            if (grid[x][y]) { res += mult; }
        }
    }
    for (int y = 0; y < 2 * n; y++) {
        int mult = 0;
        for (int x = 0; x < 2 * n; x++) {
            mult += xDirCnt[x][y];
            if (grid[x][y]) { res += mult; }
        }
    }
    cout << res << endl;
}
