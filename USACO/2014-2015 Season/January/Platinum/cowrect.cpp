#include <bits/stdc++.h>

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

#define PI acos(-1)

#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define SQ(x) ((x) * (x))

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef vector<ll> vll;
typedef vector<ull> vul;
typedef complex<ld> point;
typedef complex<ld> cld;
typedef vector<cld> vcld;

#define MAXN 500

int n;
vi ys, xs;
vector<pair<pii, char>> withX[MAXN];
vector<pair<pii, char>> cows;
pii res;

int main() {
    ifstream fin("cowrect.in");
    ofstream fout("cowrect.out");
    fin >> n;
    F0R(i, n) {
        int x, y;
        char c;
        fin >> x >> y >> c;
        cows.PB(MP(MP(x, y), c));
        ys.PB(y);
        xs.PB(x);
    }
    sort(all(ys)), sort(all(xs));
    ys.erase(unique(all(ys)), ys.end());
    xs.erase(unique(all(xs)), xs.end());
    for(auto p : cows) withX[LB(all(xs), p.F.F) - xs.begin()].PB(p);
    F0R(i, sz(ys)) FOR(j, i, sz(ys)) {
        int lo = ys[i], hi = ys[j];
        int ptr = 0;
        while(ptr < sz(xs)) {
            int minX = 1000, maxX = 0, numOn = 0;
            while(ptr < sz(xs)) {
                int numToAdd = 0;
                bool canAdd = 1;
                for(auto p : withX[ptr]) {
                    if(p.S == 'G' && p.F.S >= lo && p.F.S <= hi) canAdd = 0;
                    else if(p.S == 'H' && p.F.S >= lo && p.F.S <= hi) numToAdd++;
                }
                if(!canAdd) break;
                if(numToAdd) {
                    maxX = max(maxX, xs[ptr]);
                    minX = min(minX, xs[ptr]);
                    numOn += numToAdd;
                }
                ptr++;
            }
            res = min(res, MP(-numOn, (maxX - minX) * (hi - lo)));
            ptr++;
        }
    }
    fout << -res.F << "\n" << res.S << endl;
}
