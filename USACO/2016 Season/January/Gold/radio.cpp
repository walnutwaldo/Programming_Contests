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

int n, m, changeX[4] {1, 0, -1, 0}, changeY[4] {0, 1, 0, -1}, dp[MAXN + 1][MAXN + 1];
vector<pii> fj, b;

int dcode(char dir) {
    if(dir == 'E') return 0;
    if(dir == 'N') return 1;
    if(dir == 'W') return 2;
    return 3;
}

ll calcDis(pii p1, pii p2) {
    return SQ(p1.F - p2.F) + SQ(p1.S - p2.S);
}

ll best(int fjPlace, int bPlace) {
    if(fjPlace == 0 && bPlace == 0)
        return 0;
    if(dp[fjPlace][bPlace] != 0) return dp[fjPlace][bPlace];
    ll dis = calcDis(fj[fjPlace], b[bPlace]);
    dp[fjPlace][bPlace] = dis;
    int sub = -1;
    dp[fjPlace][bPlace] = dis;
    if(fjPlace > 0 && bPlace > 0 && (sub == -1 || best(fjPlace - 1, bPlace - 1) < sub))
        sub = best(fjPlace - 1, bPlace - 1);
    if(fjPlace > 0 && (sub == -1 || best(fjPlace - 1, bPlace) < sub))
        sub = best(fjPlace - 1, bPlace);
    if(bPlace > 0 && (sub == -1 || best(fjPlace, bPlace - 1) < sub))
        sub = best(fjPlace, bPlace - 1);
    dp[fjPlace][bPlace] += sub;
    return dp[fjPlace][bPlace];
}

int main() {
    ifstream fin("radio.in");
    ofstream fout("radio.out");
    fin >> n >> m;
    int fx, fy, bx, by;
    fin >> fx >> fy >> bx >> by;
    fj.PB(MP(fx, fy));
    b.PB(MP(bx, by));
    F0R(i, n) {
        char dir;
        fin >> dir;
        int d = dcode(dir);
        fx += changeX[d];
        fy += changeY[d];
        fj.PB(MP(fx, fy));
    }
    F0R(i, m) {
        char dir;
        fin >> dir;
        int d = dcode(dir);
        bx += changeX[d];
        by += changeY[d];
        b.PB(MP(bx, by));
    }
    fout << best(n, m) << "\n";
    return 0;
}
