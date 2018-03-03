#include <bits/stdc++.h>
#pragma pack(1)

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

const pll prime = MP(101, 97);
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

    int **pref;
    int rows, cols;
    pll hash = MP(0, 0);
    pii bottomRight;

    Figure(string* color = NULL, int rLo = 0, int rHi = 0, int cLo = 0, int cHi = 0, bool flipped = 0, int rot = 0) {
        this->rows = rHi - rLo;
        this->cols = cHi - cLo;
        if(rot & 1)
            swap(rows, cols);
        pref = new int*[rows];
        F0R(i, rows) pref[i] = new int[cols];
        doCalculations(color, rLo, cLo, flipped, rot);
    }

    char getColor(string* color, int rLo, int cLo, bool flipped, int rot, int r, int c) {
        int rr = rows, cc = cols;
        int tmp;
        F0R(i, rot) {
            tmp = r;
            r = cc - c - 1;
            c = tmp;
            swap(cc, rr);
        }
        if(flipped)
            c = cc - c - 1;
        return color[rLo + r][cLo + c];
    }

    void doCalculations(string* color, int rLo, int cLo, bool flipped, int rot) {
        F0R(r, rows) F0R(c, cols) {
            if(getColor(color, rLo, cLo, flipped, rot, r, c) > 0)
                pref[r][c] = 1, bottomRight = MP(r, c);
            else
                pref[r][c] = 0;
            if(c > 0)
                pref[r][c] += pref[r][c - 1];
            else if(r > 0)
                pref[r][c] += pref[r - 1][cols - 1];
        }
        F0R(r, n) F0R(c, m) if(r < rows && c < cols)
            hash = hash + (powPrime[r * m + c] * getColor(color, rLo, cLo, flipped, rot, r, c));
    }
};

ifstream fin("bcs.in");
ofstream fout("bcs.out");

int k;

Figure cow;
Figure pieces[MAXK][8];

pll finalHash[8 * MAXK][8 * MAXK];
pii finalOffset[8 * MAXK][8 * MAXK];

void createGroup(string *color, int rLo, int rHi, int cLo, int cHi, int i) {
        F0R(j, 4) pieces[i][j] = Figure(color, rLo, rHi, cLo, cHi, 0, j);
        F0R(j, 4) pieces[i][j + 4] = Figure(color, rLo, rHi, cLo, cHi, 1, j);
}

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
    int lo = 0, hi = n * m - 1, mid;
    while(lo < hi) {
        mid = (lo + hi) >> 1;
        if(cow.pref[mid / m][mid % m] - getPref(f, offset, mid / m, mid % m) == cutoff)
            hi = mid;
        else
            lo = mid + 1;
    }
    return MP(lo / m, lo % m);
}

pii calcBottomRight(Figure f1, pii offset1, Figure f2, pii offset2) {
    int cutoff = area(cow) - area(f1) - area(f2);
    int lo = 0, hi = n * m - 1, mid;
    while(lo < hi) {
        mid = (lo + hi) >> 1;
        if(cow.pref[mid / m][mid % m] - getPref(f1, offset1, mid / m, mid % m) - getPref(f2, offset2, mid / m, mid % m) == cutoff)
            hi = mid;
        else
            lo = mid + 1;
    }
    return MP(lo / m, lo % m);
}

bool works(int a, int aRot, int b, int bRot, int c, int cRot) {
    if(finalOffset[a * 8 + aRot][b * 8 + bRot] == MP(-1, -1)) {
        pii aOffset = cow.bottomRight - pieces[a][aRot].bottomRight;
        if(aOffset.F < 0 || aOffset.F + pieces[a][aRot].rows > n || aOffset.S < 0 || aOffset.S + pieces[a][aRot].cols > m)
            return 0;
        finalHash[a * 8 + aRot][b * 8 + bRot] = cow.hash - (pieces[a][aRot].hash * powPrime[m * aOffset.F + aOffset.S]);
        pii bOffset = calcBottomRight(pieces[a][aRot], aOffset) - pieces[b][bRot].bottomRight;
        if(bOffset.F < 0 || bOffset.F + pieces[b][bRot].rows > n || bOffset.S < 0 || bOffset.S + pieces[b][bRot].cols > m)
            return 0;
        finalHash[a * 8 + aRot][b * 8 + bRot] = finalHash[a * 8 + aRot][b * 8 + bRot] - (pieces[b][bRot].hash * powPrime[m * bOffset.F + bOffset.S]);
        finalOffset[a * 8 + aRot][b * 8 + bRot] = calcBottomRight(pieces[a][aRot], aOffset, pieces[b][bRot], bOffset);
    }
    pii cOffset = finalOffset[a * 8 + aRot][b * 8 + bRot] - pieces[c][cRot].bottomRight;
    if(cOffset.F < 0 || cOffset.F + pieces[c][cRot].rows > n || cOffset.S < 0 || cOffset.S + pieces[c][cRot].cols > m)
        return 0;
    return finalHash[a * 8 + aRot][b * 8 + bRot] == pieces[c][cRot].hash * powPrime[cOffset.F * m + cOffset.S];
}

bool worksOrdered(int a, int b, int c) {
    F0R(aRot, 8) F0R(bRot, 8) F0R(cRot, 8) if(works(a, aRot, b, bRot, c, cRot))
        return 1;
    return 0;
}

pair<string*, pair<pii, pii>> readFig() {
    int r, c;
    fin >> r >> c;
    string *color = new string[r];
    char ch;
    F0R(i, r) F0R(j, c) {
        fin >> ch;
        color[i].PB(ch - '.');
    }
    int minR = INT_MAX, maxR = 0, minC = INT_MAX, maxC = 0;
    F0R(i, r) F0R(j, c) if(color[i][j] > 0) {
        minR = min(i, minR), maxR = max(i, maxR);
        minC = min(j, minC), maxC = max(j, maxC);
    }
    return MP(color, MP(MP(minR, maxR + 1), MP(minC, maxC + 1)));
}

bool worksUnordered(int a, int b, int c) {
    if(area(pieces[a][0]) + area(pieces[b][0]) + area(pieces[c][0]) != area(cow))
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
    F0R(i, 8 * k) F0R(j, 8 * k) finalOffset[i][j] = MP(-1, -1);
    pair<string*, pair<pii, pii>> cowP = readFig();
    n = cowP.S.F.S - cowP.S.F.F, m = cowP.S.S.S - cowP.S.S.F;
    powPrime[0] = MP(1, 1);
    FOR(i, 1, n * m + 1) powPrime[i] = prime * powPrime[i - 1];
    cow = Figure(cowP.F, cowP.S.F.F, cowP.S.F.S, cowP.S.S.F, cowP.S.S.S, false, 0);
    F0R(i, k) {
        pair<string*, pair<pii, pii>> p = readFig();
        createGroup(p.F, p.S.F.F, p.S.F.S, p.S.S.F, p.S.S.S, i);
    }
    int res = 0;
    F0R(a, k) FOR(b, a + 1, k) FOR(c, b + 1, k) if(worksUnordered(a, b, c))
        res++;
    fout << res << endl;
    return 0;
}
