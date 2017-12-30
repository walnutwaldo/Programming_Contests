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
#define fig pair<vector<vector<char>>, pair<int, pii>>
#define MAXN 500
#define MAXK 100

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
unordered_map<ll, vi> withHash;
bool res[MAXK][MAXK][MAXK], withArea[MAXN * MAXN + 1];

void tryAdding(int a, int b, int i) {
    if(figure[a][0].A + figure[b][0].A + figure[i][0].A != cow.A) return;
    if(i < min(a, b)) res[i][min(a, b)][max(a, b)] = 1;
    else if(i > max(a, b)) res[min(a, b)][max(a, b)][i] = 1;
    else res[min(a, b)][i][max(a, b)] = 1;
}

void figuresWork(fig a, fig b, int aID, int bID) {
    vector<pii> q;
    bool got[cow.F.size()][cow.F[0].size()];
    F0R(row, cow.F.size()) F0R(col, cow.F[0].size()) {
        if(cow.F[row][col] != '.') q.PB(MP(row, col)), got[row][col] = 0;
        else got[row][col] = 1;
    }
    pii topLeft = q[0];
    F0R(row, a.F.size()) F0R(col, a.F[0].size()) {
        int cowR = topLeft.F + row - a.firstSpot.F;
        int cowC = topLeft.S + col - a.firstSpot.S;
        if(a.F[row][col] == '.') continue;
        if(cowR < 0 || cowR >= cow.F.size() || cowC < 0 || cowC >= cow.F[0].size() || got[cowR][cowC] || cow.F[cowR][cowC] != a.F[row][col]) return;
        got[cowR][cowC] = true;
    }
    int ptr = 0;
    while(got[q[ptr].F][q[ptr].S]) ptr++;
    topLeft = q[ptr];
    F0R(row, b.F.size()) F0R(col, b.F[0].size()) {
        int cowR = topLeft.F + row - b.firstSpot.F;
        int cowC = topLeft.S + col - b.firstSpot.S;
        if(b.F[row][col] == '.') continue;
        if(cowR < 0 || cowR >= cow.F.size() || cowC < 0 || cowC >= cow.F[0].size() || got[cowR][cowC] || cow.F[cowR][cowC] != b.F[row][col]) return;
        got[cowR][cowC] = true;
    }
    int minR = 10000, maxR = 0, minC = 10000, maxC = 0;
    F0R(row, cow.F.size()) F0R(col, cow.F[0].size()) {
        if(!got[row][col]) {
            minR = min(minR, row), maxR = max(maxR, row);
            minC = min(minC, col), maxC = max(maxC, col);
        }
    }
    ll h = 0;
    FOR(row, minR, maxR + 1) {
        FOR(col, minC, maxC + 1) {
            h *= 379;
            if(!got[row][col]) h += cow.F[row][col] - 'a' + 1;
        }
        h *= 379;
        h += 100;
    }
    if(!withHash.count(h)) return;
    for(const int i : withHash[h]) if(i != aID && i != bID) tryAdding(aID, bID, i);
}

void tryDoing(int a, int b) {
    if(figure[a][0].A + figure[b][0].A >= cow.A || !withArea[cow.A - figure[a][0].A - figure[b][0].A]) return;
    F0R(rotA, 8) F0R(rotB, 8) figuresWork(figure[a][rotA], figure[b][rotB], a, b);
}

fig readFigure() {
    int r, c;
    fin >> r >> c;
    vector<vector<char>> res(r);
    int area = 0;
    pii fs;
    F0R(row, r) {
        res[row] = vector<char>(c);
        F0R(col, c) {
            fin >> res[row][col];
            if(res[row][col] != '.') {
                area++;
                if(area == 1) fs = MP(row, col);
            }
        }
    }
    return MP(res, MP(area, fs));
}

fig rotate90(fig a) {
    vector<vector<char>> res(a.F[0].size());
    int area = 0;
    pii fs;
    F0R(row, a.F[0].size()) {
        res[row] = vector<char>(a.F.size());
        F0R(col, a.F.size()) {
            res[row][col] = a.F[a.F.size() - 1 - col][row];
            if(res[row][col] != '.') {
                area++;
                if(area == 1) fs = MP(row, col);
            }
        }
    }
    return MP(res, MP(area, fs));
}

fig flipHoriz(fig a) {
    vector<vector<char>> res(a.F.size());
    int area = 0;
    pii fs;
    F0R(row, a.F.size()) {
        res[row] = vector<char>(a.F[0].size());
        F0R(col, a.F[0].size()) {
            res[row][col] = a.F[row][a.F[0].size() - 1 - col];
            if(res[row][col] != '.') {
                area++;
                if(area == 1) fs = MP(row, col);
            }
        }
    }
    return MP(res, MP(area, fs));
}

ll getHash(fig a) {
    ll h = 0;
    F0R(row, a.F.size()) {
        F0R(col, a.F[0].size()) {
            h *= 379;
            if(a.F[row][col] != '.') h += a.F[row][col] - 'a' + 1;
        }
        h *= 379;
        h += 100;
    }
    return h;
}

int main() {
    fin >> k;
    cow = readFigure();
    F0R(i, k) {
        figure[i][0] = readFigure();
        withArea[figure[i][0].A] = 1;
        FOR(j, 1, 4) figure[i][j] = rotate90(figure[i][j - 1]);
        figure[i][4] = flipHoriz(figure[i][0]);
        FOR(j, 5, 8) figure[i][j] = rotate90(figure[i][j - 1]);
        unordered_set<ll> s;
        F0R(j, 8) {
            ll h = getHash(figure[i][j]);
            if(s.count(h)) continue;
            s.insert(h);
            if(!withHash.count(h)) withHash.insert(MP(h, vi()));
            withHash[h].PB(i);
        }
    }
    F0R(a, k) F0R(b, k) if(a != b) tryDoing(a, b);
    int total = 0;
    F0R(a, k) F0R(b, k) F0R(c, k) if(res[a][b][c]) total++;
    fout << total << "\n";
    return 0;
}
