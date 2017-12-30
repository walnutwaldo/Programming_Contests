// Too slow
#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define F first
#define S second
#define A second.first
#define firstSpot second.second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define fig pair<vector<vector<char>>, pair<int*, pii>>
#define MAXN 500
#define MAXK 100
#define MAXR 500

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

ifstream fin("bcs.in");
ofstream fout("bcs.out");
int k;
fig cow;
fig figure[MAXK][8];

bool figuresWork(fig a, fig b, fig c) {
    vector<pii> q;
    bool got[cow.F.size()][cow.F[0].size()];
    F0R(row, cow.F.size()) F0R(col, cow.F[0].size()) {
        if(cow.F[row][col] != '.') q.PB(MP(row, col)), got[row][col] = 0;
        else got[row][col] = 1;
    }
    int ptr = 0;
    while(got[q[ptr].F][q[ptr].S]) ptr++;
    pii topLeft = q[ptr];
    F0R(row, a.F.size()) F0R(col, a.F[0].size()) {
        int cowR = topLeft.F + row - a.firstSpot.F;
        int cowC = topLeft.S + col - a.firstSpot.S;
        if(a.F[row][col] == '.') continue;
        if(cowR < 0 || cowR >= cow.F.size() || cowC < 0 || cowC >= cow.F[0].size() || got[cowR][cowC] || cow.F[cowR][cowC] != a.F[row][col]) return false;
        got[cowR][cowC] = true;
    }
    while(got[q[ptr].F][q[ptr].S]) ptr++;
    topLeft = q[ptr];
    F0R(row, b.F.size()) F0R(col, b.F[0].size()) {
        int cowR = topLeft.F + row - b.firstSpot.F;
        int cowC = topLeft.S + col - b.firstSpot.S;
        if(b.F[row][col] == '.') continue;
        if(cowR < 0 || cowR >= cow.F.size() || cowC < 0 || cowC >= cow.F[0].size() || got[cowR][cowC] || cow.F[cowR][cowC] != b.F[row][col]) return false;
        got[cowR][cowC] = true;
    }
    while(got[q[ptr].F][q[ptr].S]) ptr++;
    topLeft = q[ptr];
    F0R(row, c.F.size()) F0R(col, c.F[0].size()) {
        int cowR = topLeft.F + row - c.firstSpot.F;
        int cowC = topLeft.S + col - c.firstSpot.S;
        if(c.F[row][col] == '.') continue;
        if(cowR < 0 || cowR >= cow.F.size() || cowC < 0 || cowC >= cow.F[0].size() || got[cowR][cowC] || cow.F[cowR][cowC] != c.F[row][col]) return false;
        got[cowR][cowC] = true;
    }
    return true;
}

bool orderedTripleWorks(int a, int b, int c) {
    F0R(rotA, 8) F0R(rotB, 8) F0R(rotC, 8) if(figuresWork(figure[a][rotA], figure[b][rotB], figure[c][rotC])) return true;
    return false;
}

bool tripleWorks(int a, int b, int c) {
    F0R(i, 26)
    if(figure[a][0].A[i] + figure[b][0].A[i] + figure[c][0].A[i] != cow.A[i]) return false;
    if(orderedTripleWorks(a, b, c)) return true;
    if(orderedTripleWorks(a, c, b)) return true;
    if(orderedTripleWorks(b, a, c)) return true;
    if(orderedTripleWorks(b, c, a)) return true;
    if(orderedTripleWorks(c, a, b)) return true;
    if(orderedTripleWorks(c, b, a)) return true;
    return false;
}

fig readFigure() {
    int r, c;
    fin >> r >> c;
    vector<vector<char>> res(r);
    int *area = new int[26];
    memset(area, 0, 26 * sizeof(int));
    pii fs = MP(10000, 10000);
    F0R(row, r) {
        res[row] = vector<char>(c);
        F0R(col, c) {
            fin >> res[row][col];
            if(res[row][col] != '.') {
                area[res[row][col] - 'a']++;
                fs = min(fs, MP(row, col));
            }
        }
    }
    return MP(res, MP(area, fs));
}

fig rotate90(fig a) {
    vector<vector<char>> res(a.F[0].size());
    int *area = new int[26];
    memset(area, 0, 26 * sizeof(int));
    pii fs = MP(10000, 10000);
    F0R(row, a.F[0].size()) {
        res[row] = vector<char>(a.F.size());
        F0R(col, a.F.size()) {
            res[row][col] = a.F[a.F.size() - 1 - col][row];
            if(res[row][col] != '.') {
                area[res[row][col] - 'a']++;
                fs = min(fs, MP(row, col));
            }
        }
    }
    return MP(res, MP(area, fs));
}

fig flipHoriz(fig a) {
    vector<vector<char>> res(a.F.size());
    int *area = new int[26];
    memset(area, 0, 26 * sizeof(int));
    pii fs = MP(10000, 10000);
    F0R(row, a.F.size()) {
        res[row] = vector<char>(a.F[0].size());
        F0R(col, a.F[0].size()) {
            res[row][col] = a.F[row][a.F[0].size() - 1 - col];
            if(res[row][col] != '.') {
                area[res[row][col] - 'a']++;
                fs = min(fs, MP(row, col));
            }
        }
    }
    return MP(res, MP(area, fs));
}

int main() {
    fin >> k;
    cow = readFigure();
    F0R(i, k) {
        figure[i][0] = readFigure();
        FOR(j, 1, 4) figure[i][j] = rotate90(figure[i][j - 1]);
        figure[i][4] = flipHoriz(figure[i][0]);
        FOR(j, 5, 8) figure[i][j] = rotate90(figure[i][j - 1]);
    }
    int res = 0;
    F0R(a, k) FOR(b, a + 1, k) FOR(c, b + 1, k) res += tripleWorks(a, b, c);
    fout << res << "\n";
    return 0;
}
