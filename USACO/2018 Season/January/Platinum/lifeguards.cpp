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
#define R real()
#define I image()
#define PI acos(-1)
#define MAXK 100
#define MAXN 100000

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;
typedef complex<ld> cld;

struct Case {

    ll best;
    ll stop;

    Case(ll bb = 0, ll ss = 0) {
        best = bb, stop = ss;
    }

    ll getAt(ll curr) {
        if(curr >= stop) return best;
        return best + curr - stop;
    }

};

int n, k;
vector<pair<ll, ll>> shifts, sa;
int pileLoc[MAXK + 1], pileLo[MAXK + 1], pileHi[MAXK + 1];
Case pile[MAXK + 1][MAXN];

void insertToPile(int pileID, Case c) {
    int p = pileLoc[pileID];
    while(pileHi[p] - pileLo[p]) {
        if(c.getAt(pile[p][pileHi[p] - 1].stop) >= pile[p][pileHi[p] - 1].best) pileHi[p]--;
        else break;
    }
    if(pileHi[p] - pileLo[p] == 0 || c.best > pile[p][pileHi[p] - 1].best) pile[p][pileHi[p]++] = c;
}

Case bestCase(int pileID, ll curr) {
    int p = pileLoc[pileID];
    while(pileHi[p] - pileLo[p] > 1) {
        if(pile[p][pileLo[p]].getAt(curr) <= pile[p][pileLo[p] + 1].getAt(curr)) pileLo[p]++;
        else break;
    }
    return pile[p][pileLo[p]];
}

void moveOn() {
    F0R(i, k + 1) pileLoc[i] = (pileLoc[i] + k) % (k + 1);
    pileLo[pileLoc[0]] = 0;
    pileHi[pileLoc[0]] = 0;
}

void printPiles() {
    F0R(i, k + 1) {
        cout << i << ": ";
        int p = pileLoc[i];
        FOR(j, pileLo[p], pileHi[p]) cout << "(" << pile[p][j].best << " " << pile[p][j].stop << ") ";
        cout << endl;
    }
}

void solve() {
    F0R(i, k + 1) pileLoc[i] = i;
    pileHi[0]++;
    F0R(i, n) {
        Case best0 = bestCase(0, sa[i].F);
        Case toAddTo0(best0.getAt(sa[i].F) + sa[i].S - sa[i].F, sa[i].S);
        FOR(j, 1, k + 1) {
            if(pileHi[pileLoc[j]] - pileLo[pileLoc[j]] == 0) continue;
            Case best = bestCase(j, sa[i].F);
            insertToPile(j - 1, Case(best.getAt(sa[i].F) + sa[i].S - sa[i].F, sa[i].S));
        }
        moveOn();
        insertToPile(0, toAddTo0);
    }
}

int main() {
    ifstream fin("lifeguards.in");
    ofstream fout("lifeguards.out");
    fin >> n >> k;
    F0R(i, n) {
        pair<ll, ll> shift;
        fin >> shift.F >> shift.S;
        shifts.PB(shift);
    }
    sort(shifts.begin(), shifts.end());
    int hiEnd = -1;
    int realK = k;
    F0R(i, n) {
        if(shifts[i].S > hiEnd) sa.PB(shifts[i]), hiEnd = shifts[i].S;
        else realK--;
    }
    n += realK - k;
    k = max(0, realK);
    solve();
    fout << bestCase(k, 1000000002LL).getAt(1000000002LL) << endl;
    return 0;
}
