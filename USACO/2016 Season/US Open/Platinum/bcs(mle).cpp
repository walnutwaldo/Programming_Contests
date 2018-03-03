#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define ran() (rand() & 0x7FFF)
#define rand31() ((ran() << 16) | (ran() << 1) | (ran() & 1))
#define rand32() ((ran() << 17) | (ran() << 2) | (ran() & 3))
#define rand63() (((ll)ran() << 48) | ((ll)ran() << 33) | ((ll)ran() << 18) | ((ll)ran() << 3) | ((ll)ran() & 7))
#define rand64() (((ll)ran() << 49) | ((ll)ran() << 34) | ((ll)ran() << 19) | ((ll)ran() << 4) | ((ll)ran() & 15))

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define X real()
#define Y imag()
#define MAXK 100
#define MAXN 500
#define MOD 1000000007

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef complex<ld> point;

const pll prime = MP(73, 97);
pll powPrime[SQ(MAXN) + 1];

pll operator +(pll p1, pll p2) {
    return MP((p1.F + p2.F) % MOD, (p1.S + p2.S) % MOD);
}

pll operator -(pll p1, pll p2) {
    return MP((p1.F + MOD -  p2.F) % MOD, (p1.S + MOD - p2.S) % MOD);
}

pll operator *(pll p1, pll p2) {
    return MP((p1.F * p2.F) % MOD, (p1.S * p2.S) % MOD);
}

pll operator *(pll p, ll l) {
    return p * MP(l, l);
}

pii operator -(pii p1, pii p2) {
    return MP(p1.F - p2.F, p1.S - p2.S);
}

int n, m, minArea;

struct Figure {

    short **color;
    int **pref;
    int rows, cols;
    pll hash = MP(0, 0);
    pii bottomRight;

    Figure(int rows = 0, int cols = 0) {
        this->rows = rows;
        this->cols = cols;
        color = new short*[rows];
        F0R(i, rows) color[i] = new short[cols];
        pref = new int*[rows];
        F0R(i, rows) pref[i] = new int[cols];
    }

    void doCalculations() {
        F0R(r, rows) F0R(c, cols) {
            pref[r][c] = color[r][c] > 0;
            if(c > 0)
                pref[r][c] += pref[r][c - 1];
            else if(r > 0)
                pref[r][c] += pref[r - 1][cols - 1];
            if(color[r][c] > 0)
                bottomRight = MP(r, c);
        }
        F0R(r, n) F0R(c, m) if(r < rows && c < cols)
            hash = hash + (powPrime[r * m + c] * color[r][c]);
    }
};

struct FigureGroup {

    Figure figs[8];

    FigureGroup(Figure f = Figure()) {
        figs[0] = f;
        figs[1] = flip(figs[0]);
        FOR(i, 2, 8) figs[i] = rot(figs[i - 2]);
        F0R(i, 8) figs[i].doCalculations();
    }

    Figure rot(Figure a) {
        Figure res(a.cols, a.rows);
        F0R(i, a.rows) F0R(j, a.cols) res.color[j][a.rows - i - 1] = a.color[i][j];
        return res;
    }

    Figure flip(Figure a) {
        Figure res(a.rows, a.cols);
        F0R(i, a.rows) F0R(j, a.cols) res.color[i][a.cols - j - 1] = a.color[i][j];
        return res;
    }

};

ifstream fin("bcs.in");
ofstream fout("bcs.out");

int k;

Figure cow;
FigureGroup pieces[MAXK];

bool calculated[8 * MAXK][8 * MAXK];
pll finalHash[8 * MAXK][8 * MAXK];
pii finalOffset[8 * MAXK][8 * MAXK];

int area(Figure f) {
    return f.pref[f.rows - 1][f.cols - 1];
}

int getPref(Figure f, pii offset, int r, int c) {
    r -= offset.F, c -= offset.S;
    if(r >= f.rows)
        return area(f);
    c = min(c, f.cols - 1);
    if(c < 0)
        r--, c = f.cols - 1;
    if(r >= 0)
        return f.pref[r][c];
    return 0;
}

pii calcBottomRight(Figure f, pii offset) {
    int cutoff = area(cow) - area(f);
    int lo = 0, hi = n * m - 1;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(cow.pref[mid / m][mid % m] - getPref(f, offset, mid / m, mid % m) == cutoff)
            hi = mid;
        else
            lo = mid + 1;
    }
    return MP(lo / m, lo % m);
}

pii calcBottomRight(Figure f1, pii offset1, Figure f2, pii offset2) {
    int cutoff = area(cow) - area(f1) - area(f2);
    int lo = 0, hi = n * m - 1;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(cow.pref[mid / m][mid % m] - getPref(f1, offset1, mid / m, mid % m) - getPref(f2, offset2, mid / m, mid % m) == cutoff)
            hi = mid;
        else
            lo = mid + 1;
    }
    return MP(lo / m, lo % m);
}

bool works(Figure aFig, Figure bFig, Figure cFig, int a, int b) {
    if(!calculated[a][b]) {
        pii aOffset = cow.bottomRight - aFig.bottomRight;
        if(aOffset.F < 0 || aOffset.F + aFig.rows > n || aOffset.S < 0 || aOffset.S + aFig.cols > m)
            return 0;
        finalHash[a][b] = cow.hash - (aFig.hash * powPrime[m * aOffset.F + aOffset.S]);
        pii bOffset = calcBottomRight(aFig, aOffset) - bFig.bottomRight;
        if(bOffset.F < 0 || bOffset.F + bFig.rows > n || bOffset.S < 0 || bOffset.S + bFig.cols > m)
            return 0;
        finalHash[a][b] = finalHash[a][b] - (bFig.hash * powPrime[m * bOffset.F + bOffset.S]);
        finalOffset[a][b] = calcBottomRight(aFig, aOffset, bFig, bOffset);
        calculated[a][b] = 1;
    }
    pii cOffset = finalOffset[a][b] - cFig.bottomRight;
    if(cOffset.F < 0 || cOffset.F + cFig.rows > n || cOffset.S < 0 || cOffset.S + cFig.cols > m)
        return 0;
    return finalHash[a][b] == cFig.hash * powPrime[cOffset.F * m + cOffset.S];
}

bool worksOrdered(int a, int b, int c) {
    F0R(aRot, 8) F0R(bRot, 8) F0R(cRot, 8) if(works(pieces[a].figs[aRot], pieces[b].figs[bRot], pieces[c].figs[cRot], a * 8 + aRot, b * 8 + bRot))
        return 1;
    return 0;
}

Figure readFig() {
    int r, c;
    fin >> r >> c;
    char **color = new char*[r];
    F0R(i, r) color[i] = new char[c];
    F0R(i, r) F0R(j, c) fin >> color[i][j];
    int minR = INT_MAX, maxR = 0, minC = INT_MAX, maxC = 0;
    F0R(i, r) F0R(j, c) if(color[i][j] != '.') {
        minR = min(i, minR), maxR = max(i, maxR);
        minC = min(j, minC), maxC = max(j, maxC);
    }
    Figure res(maxR - minR + 1, maxC - minC + 1);
    F0R(i, maxR - minR + 1) F0R(j, maxC - minC + 1) res.color[i][j] = color[minR + i][minC + j] == '.'?0:(color[minR + i][minC + j] - 'a' + 1);
    return res;
}

bool worksUnordered(int a, int b, int c) {
    if(area(pieces[a].figs[0]) + area(pieces[b].figs[0]) + area(pieces[c].figs[0]) != area(cow))
        return 0;
    if(worksOrdered(a, b, c))
        return 1;
    if(worksOrdered(a, c, b))
        return 1;
    if(worksOrdered(b, a, c))
        return 1;
    if(worksOrdered(b, c, a))
        return 1;
    if(worksOrdered(c, a, b))
        return 1;
    if(worksOrdered(c, b, a))
        return 1;
    return 0;
}

int main() {
    fin >> k;
    cow = readFig();
    n = cow.rows, m = cow.cols;
    powPrime[0] = MP(1, 1);
    FOR(i, 1, n * m + 1) powPrime[i] = prime * powPrime[i - 1];
    cow.doCalculations();
    minArea = INT_MAX;
    F0R(i, k) pieces[i] = FigureGroup(readFig());
    F0R(i, k) minArea = min(minArea, area(pieces[i].figs[0]));
    int res = 0;
    F0R(a, k) FOR(b, a + 1, k) FOR(c, b + 1, k) if(worksUnordered(a, b, c))
        res++;
    fout << res << endl;
    return 0;
}
