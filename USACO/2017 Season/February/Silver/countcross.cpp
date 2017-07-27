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
#define MAXN 100
#define MAXK 100

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int N, K, R;
bool road[MAXN][MAXN][4];
pii parent[MAXN][MAXN], cows[MAXK];

pii root(pii xy) {
    if(parent[xy.F][xy.S] == xy)
        return xy;
    pii r = root(parent[xy.F][xy.S]);
    parent[xy.F][xy.S] = r;
    return r;
}

void mergeTrees(pii t1, pii t2) {
    pii r1,r2;
    r1 = root(t1);
    r2 = root(t2);
    if(r1 == r2)
        return;
    parent[r2.F][r2.S] = r1;
}

int main() {
    ifstream fin("countcross.in");
    ofstream fout("countcross.out");

    fin >> N >> K >> R;
    F0R(i, R) {
        int x1, y1, x2, y2;
        fin >> x1 >> y1 >> x2 >> y2;
        x1--;
        y1--;
        x2--;
        y2--;
        if(x2 > x1) {
            road[x1][y1][0] = true;
            road[x2][y2][2] = true;
        }
        if(x2 < x1) {
            road[x1][y1][2] = true;
            road[x2][y2][0] = true;
        }
        if(y2 > y1) {
            road[x1][y1][1] = true;
            road[x2][y2][3] = true;
        }
        if(y2 < y1) {
            road[x1][y1][3] = true;
            road[x2][y2][1] = true;
        }
    }
    F0R(i, K) {
        int x, y;
        fin >> x >> y;
        x--;
        y--;
        cows[i] = MP(x, y);
    }
    F0R(x, N) F0R(y, N) {
        parent[x][y] = MP(x, y);
        if(x == 0) road[x][y][2] = true;
        if(x == N - 1) road[x][y][0] = true;
        if(y == 0) road[x][y][3] = true;
        if(y == N - 1) road[x][y][1] = true;
    }
    F0R(x, N) F0R(y, N) {
        if(!road[x][y][0]) mergeTrees(MP(x, y), MP(x + 1, y));
        if(!road[x][y][1]) mergeTrees(MP(x, y), MP(x, y + 1));
        if(!road[x][y][2]) mergeTrees(MP(x, y), MP(x - 1, y));
        if(!road[x][y][3]) mergeTrees(MP(x, y), MP(x, y - 1));
    }
    ll res = 0;
    F0R(i, K) FOR(j, i + 1, K) {
        if(root(cows[i]) != root(cows[j]))
            res++;
    }
    fout << res << endl;
    return 0;
}
