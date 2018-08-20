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
#define MAXN 20

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, component[MAXN][MAXN], res;
char color[MAXN][MAXN];
bool doesntwork[MAXN][MAXN][MAXN][MAXN];

void process(int x1, int y1, int x2, int y2) {
    res++;
    FOR(x3, x1, x2 + 1) FOR(x4, x3, x2 + 1) FOR(y3, y1, y2 + 1) FOR(y4, y3, y2 + 1) {
        doesntwork[x3][y3][x4][y4] = true;
    }
}

void dfs(int x, int y, int x1, int y1, int x2, int y2, int comp) {
    component[x][y] = comp;
    if(x > x1 && component[x - 1][y] == 0 && color[x - 1][y] == color[x][y]) dfs(x - 1, y, x1, y1, x2, y2, comp);
    if(x < x2 && component[x + 1][y] == 0 && color[x + 1][y] == color[x][y]) dfs(x + 1, y, x1, y1, x2, y2, comp);
    if(y > y1 && component[x][y - 1] == 0 && color[x][y - 1] == color[x][y]) dfs(x, y - 1, x1, y1, x2, y2, comp);
    if(y < y2 && component[x][y + 1] == 0 && color[x][y + 1] == color[x][y]) dfs(x, y + 1, x1, y1, x2, y2, comp);
}

void test(int x1, int y1, int x2, int y2) {
    int numColors = 0;
    char color1 = 'a', color2 = 'a';
    FOR(x, x1, x2 + 1) FOR(y, y1, y2 + 1) {
        if(color1 != color[x][y] && color2 != color[x][y]) {
            numColors++;
            if(color1 == 'a') {
                color1 = color[x][y];
            } else if(color2 == 'a') {
                color2 = color[x][y];
            } else {
                doesntwork[x1][y1][x2][y2] = true;
                return;
            }
        }
    }
    if(numColors < 2) {
        doesntwork[x1][y1][x2][y2] = true;
        return;
    }
    FOR(x, x1, x2 + 1) FOR(y, y1, y2 + 1) component[x][y] = 0;
    int numColor1 = 0, numColor2 = 0;
    int currc = 1;
    FOR(x, x1, x2 + 1) FOR(y, y1, y2 + 1) {
        if(component[x][y] == 0) {
            if(color[x][y] == color1) {
                numColor1++;
            } else {
                numColor2++;
            }
            dfs(x, y, x1, y1, x2, y2, currc++);
        }
    }

    if((numColor1 == 1 && numColor2 >= 2) || (numColor1 >= 2 && numColor2 == 1)) {
        process(x1, y1, x2, y2);
    } else {
        doesntwork[x1][y1][x2][y2] = true;
        return;
    }
}

int main() {
    ifstream fin("where.in");
    ofstream fout("where.out");

    fin >> n;
    F0R(y, n) F0R(x, n) {
        fin >> color[x][y];
    }

    ROF(shorter, n + 1, 1) {
        ROF(width, n + 1, shorter + 1) {
            F0R(x, n + 1 - shorter) F0R(y, n + 1 - width) {
                if(doesntwork[x][y][x + shorter - 1][y + width - 1])
                    continue;
                test(x, y, x + shorter - 1, y + width - 1);
            }
        }
        ROF(length, n + 1, shorter + 1) {
            F0R(x, n + 1 - length) F0R(y, n + 1 - shorter) {
                if(doesntwork[x][y][x + length - 1][y + shorter - 1])
                    continue;
                test(x, y, x + length - 1, y + shorter - 1);
            }
        }
        F0R(x, n + 1 - shorter) F0R(y, n + 1 - shorter) {
            if(doesntwork[x][y][x + shorter - 1][y + shorter - 1])
                continue;
            test(x, y, x + shorter - 1, y + shorter - 1);
        }
    }
    fout << res << endl;
    return 0;
}
