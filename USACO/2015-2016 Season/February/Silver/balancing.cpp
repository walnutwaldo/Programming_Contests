#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

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

int n;
bool isPoint[MAXN][MAXN];
int ul[MAXN][MAXN], dl[MAXN][MAXN], ur[MAXN][MAXN], dr[MAXN][MAXN];
vector<pii> points;
map<int, int> compX, compY;

int main() {
    ifstream fin("balancing.in");
    ofstream fout("balancing.out");
    fin >> n;
    set<int> xs, ys;
    F0R(i, n) {
        int x, y;
        fin >> x >> y;
        points.PB(MP(x,y));
        xs.insert(x);
        ys.insert(y);
    }
    int numX = xs.size();
    int numY = ys.size();
    F0R(i, numX) {
        compX[*(xs.begin())] = i;
        xs.erase(*xs.begin());
    }
    F0R(i, numY) {
        compY[*(ys.begin())] = i;
        ys.erase(*ys.begin());
    }
    for(const pii point: points) isPoint[compX[point.F]][compY[point.S]] = true;
    F0R(x, numX) F0R(y, numY) {
        if(x > 0) ul[x][y] += ul[x - 1][y];
        if(y > 0) ul[x][y] += ul[x][y - 1];
        if(x > 0 && y > 0) ul[x][y] -= ul[x - 1][y - 1];
        if(isPoint[x][y]) ul[x][y]++;
    }
    R0F(x, numX) F0R(y, numY) {
        if(x < numX - 1) ur[x][y] += ur[x + 1][y];
        if(y > 0) ur[x][y] += ur[x][y - 1];
        if(x < numX - 1 && y > 0) ur[x][y] -= ur[x + 1][y - 1];
        if(isPoint[x][y]) ur[x][y]++;
    }
    F0R(x, numX) R0F(y, numY) {
        if(x > 0) dl[x][y] += dl[x - 1][y];
        if(y < numY - 1) dl[x][y] += dl[x][y + 1];
        if(x > 0 && y < numY - 1) dl[x][y] -= dl[x - 1][y + 1];
        if(isPoint[x][y]) dl[x][y]++;
    }
    R0F(x, numX) R0F(y, numY) {
        if(x < numX - 1) dr[x][y] += dr[x + 1][y];
        if(y < numY - 1) dr[x][y] += dr[x][y + 1];
        if(x < numX - 1 && y < numY - 1) dr[x][y] -= dr[x + 1][y + 1];
        if(isPoint[x][y]) dr[x][y]++;
    }
    int M = INT_MAX;
    F0R(i, numX - 1) F0R(j, numY - 1) {
        M = min(M, max(max(ul[i][j], ur[i + 1][j]), max(dl[i][j + 1], dr[i + 1][j + 1])));
    }
    fout << M << "\n";
    return 0;
}
