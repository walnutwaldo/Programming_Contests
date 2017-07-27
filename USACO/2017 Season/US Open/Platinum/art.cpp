#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (a) - 1; i >= (b); i--)

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MAXN 1000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, minX[MAXN * MAXN + 1], maxX[MAXN * MAXN + 1], minY[MAXN * MAXN + 1], maxY[MAXN * MAXN + 1];
int numColors, color[MAXN + 1][MAXN + 1], num[MAXN + 1][MAXN + 1];
bool notPossible[MAXN * MAXN + 1];

int main() {
    ifstream fin("art.in");
    ofstream fout("art.out");

    fin >> n;
    FOR(y, 1, n + 1) FOR(x, 1, n + 1) {
        fin >> color[x][y];
        if(color[x][y] == 0) continue;
        if(minX[color[x][y]] == 0) {
            numColors++;
            minX[color[x][y]] = x;
            minY[color[x][y]] = y;
        }
        minX[color[x][y]] = min(minX[color[x][y]], x);
        maxX[color[x][y]] = max(maxX[color[x][y]], x);
        minY[color[x][y]] = min(minY[color[x][y]], y);
        maxY[color[x][y]] = max(maxY[color[x][y]], y);
    }
    if(numColors == 1) {
        if(n == 1) fout << 1 << endl;
        else fout << SQ(n) - 1 << endl;
        return 0;
    }
    FOR(col, 1, SQ(n) + 1) {
        if(minX[col] == 0) continue;
        num[minX[col]][minY[col]]++;
        if(maxX[col] < n) num[maxX[col] + 1][minY[col]]--;
        if(maxY[col] < n) num[minX[col]][maxY[col] + 1]--;
        if(maxX[col] < n && maxY[col] < n) num[maxX[col] + 1][maxY[col] + 1]++;
    }
    FOR(y, 1, n + 1) FOR(x, 2, n + 1) {
        num[x][y] +=num[x - 1][y];
    }
    FOR(y, 2, n + 1) FOR(x, 1, n + 1) {
        num[x][y] +=num[x][y - 1];
    }
    FOR(col, 1, SQ(n) + 1) {
        if(minX[col] == 0) continue;
        FOR(x, minX[col], maxX[col] + 1) FOR(y, minY[col], maxY[col] + 1) if(color[x][y] == col && num[x][y] > 1) {
            notPossible[col] = true;
            break;
        }
    }
    int res = 0;
    FOR(i, 1, SQ(n) + 1) if(!notPossible[i]) res++;
    fout << res << endl;
    return 0;
}
