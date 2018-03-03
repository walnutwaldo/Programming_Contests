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

int n, m;

struct Figure {

    char **color;
    int **pref;
    int rows, cols;
    pll hash = MP(0, 0);
    pii bottomRight;

    Figure(int rows = 0, int cols = 0) {
        this->rows = rows;
        this->cols = cols;
        color = new char*[rows];
        F0R(i, rows) color[i] = new char[cols];
        pref = new int*[rows];
        F0R(i, rows) pref[i] = new int[cols];
    }

    void doCalculations() {
        F0R(r, rows) F0R(c, cols) {
            pref[r][c] = color[r][c] != '.';
            if(c > 0)
                pref[r][c] += pref[r][c - 1];
            else if(r > 0)
                pref[r][c] += pref[r - 1][cols - 1];
            if(color[r][c] != '.')
                bottomRight = MP(r, c);
        }
        F0R(r, n) F0R(c, m) {
            if(r < rows && c < cols && color[r][c] != '.')
                hash = hash + (powPrime[r * m + c] * (color[r][c] - 'a' + 1));
        }
    }

    void print() {
        F0R(r, rows) {
            F0R(c, cols) cout << color[r][c];
            cout << endl;
        }
        cout << endl;
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
bool tripleWorks[MAXK][MAXK][MAXK];

map<pll, vi> mp;

Figure cow;
FigureGroup pieces[MAXK];

int area(Figure f) {
    return f.pref[f.rows - 1][f.cols - 1];
}

void addAnswer(int a, int b, int c) {
    tripleWorks[min(a, min(b, c))][max(a,b) ^ max(a, c) ^ max(b, c)][max(a, max(b, c))] = 1;
}

void addWith(pll h, int a, int b) {
    if(mp.count(h))
        for(const int c : mp[h])
            addAnswer(a, b, c);
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

void work(Figure aFig, Figure bFig, int a, int b) {
    pii aOffset = cow.bottomRight - aFig.bottomRight;
    if(aOffset.F < 0 || aOffset.F + aFig.rows > n || aOffset.S < 0 || aOffset.S + aFig.cols > m)
        return;
    pll h = cow.hash - (aFig.hash * powPrime[m * aOffset.F + aOffset.S]);
    pii bOffset = calcBottomRight(aFig, aOffset) - bFig.bottomRight;
    if(bOffset.F < 0 || bOffset.F + bFig.rows > n || bOffset.S < 0 || bOffset.S + bFig.cols > m)
        return;
    h = h - (bFig.hash * powPrime[m * bOffset.F + bOffset.S]);
    addWith(h, a, b);
}

void test(int a, int b) {
    cout << a << " " << b << endl;
    if(area(pieces[a].figs[0]) + area(pieces[b].figs[0]) >= area(cow))
        return;
    F0R(aRot, 8) F0R(bRot, 8) work(pieces[a].figs[aRot], pieces[b].figs[bRot], a, b);
    F0R(aRot, 8) F0R(bRot, 8) work(pieces[b].figs[bRot], pieces[a].figs[aRot], b, a);
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
    F0R(i, maxR - minR + 1) F0R(j, maxC - minC + 1) res.color[i][j] = color[minR + i][minC + j];
    return res;
}

void print(pll p) {
    cout << "(" << p.F << ", " << p.S << ")" << endl;
}

int main() {
    fin >> k;
    cow = readFig();
    n = cow.rows, m = cow.cols;
    powPrime[0] = MP(1, 1);
    FOR(i, 1, n * m + 1) powPrime[i] = prime * powPrime[i - 1];
    cow.doCalculations();
    F0R(i, k) pieces[i] = FigureGroup(readFig());
    F0R(i, k) F0R(j, 8) {
        cout << i << " " << j << endl;
        Figure f = pieces[i].figs[j];
        F0R(rShift, n - f.rows + 1) F0R(cShift, m - f.cols + 1) {
            int po = rShift * m + cShift;
            pll h = f.hash * powPrime[po];
            if(!mp.count(h))
                mp.insert(MP(h, vi()));
            if(mp[h].empty() || mp[h].back() != i)
                mp[h].PB(i);
        }
    }
    F0R(a, k) FOR(b, a + 1, k) test(a, b);
    int res = 0;
    F0R(a, k) FOR(b, a + 1, k) FOR(c, b + 1, k) if(tripleWorks[a][b][c])
        res++;
    fout << res << endl;
    return 0;
}
