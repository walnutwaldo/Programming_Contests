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
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define MAXN 1000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, m, type[MAXN][MAXN];
int best[MAXN][MAXN][2];
priority_queue<tuple<int, int, int, bool>, vector<tuple<int, int, int, bool>>, greater<tuple<int, int, int, bool>>> q;

void add(int x, int y, int d, bool s) {
    if(best[x][y][s] == -1 || d < best[x][y][s]) {
        q.push(MT(d, x, y, s));
        best[x][y][s] = d;
    }
}

void tryMoving(int x, int y, int dis, bool smell, int dx, int dy) {
    if(x < 0 || x >= n || y < 0 || y >= m) return;
    if(type[x][y] == 0) return;
    if(type[x][y] == 1) add(x, y, dis, smell);
    if(type[x][y] == 2) add(x, y, dis, true);
    if(type[x][y] == 3 && smell) add(x, y, dis, smell);
    if(type[x][y] == 4) {
        while(type[x][y] == 4) {
            int nx = x + dx;
            int ny = y + dy;
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) break;
            if(type[nx][ny] == 0 || (type[nx][ny] == 3 && !smell)) break;
            x = nx;
            y = ny;
            dis++;
        }
        add(x, y, dis, false);
    }
}

int main() {
    ifstream fin("dream.in");
    ofstream fout("dream.out");
    fin >> n >> m;
    F0R(i, n) F0R(j, m) {
        fin >> type[i][j];
        best[i][j][0] = -1;
        best[i][j][1] = -1;
    }
    add(0, 0, 0, false);
    while(!q.empty()) {
        tuple<int, int, int, bool> state = q.top();
        q.pop();
        int dis = get<0>(state);
        int x = get<1>(state);
        int y = get<2>(state);
        bool smell = get<3>(state);
        if(x == n - 1 && y == m - 1) {
            fout << dis << "\n";
            return 0;
        }
        tryMoving(x - 1, y, dis + 1, smell, -1, 0);
        tryMoving(x + 1, y, dis + 1, smell, 1, 0);
        tryMoving(x, y - 1, dis + 1, smell, 0, -1);
        tryMoving(x, y + 1, dis + 1, smell, 0, 1);
    }
    fout << "-1\n";
    return 0;
}
