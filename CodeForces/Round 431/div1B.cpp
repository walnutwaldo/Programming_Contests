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
#define X real()
#define Y imag()
#define MAXN 100000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n, w, h;
pii positions[MAXN];
pii endPos[MAXN];
int diagonal[MAXN], g[MAXN];
vector<pii> longList;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> w >> h;
    F0R(i, n) {
        int g, p, t;
        cin >> g >> p >> t;
        if(g == 1) {
            positions[i] = MP(p, -t);
            endPos[i] = MP(p, h);
        } else {
            positions[i] = MP(-t, p);
            endPos[i] = MP(w, p);
        }
        diagonal[i] = p - t;
        longList.PB(MP(diagonal[i], i));
    }
    sort(longList.begin(), longList.end());
    int currDiag = INT_MIN;
    vector<pii> inDiag;
    vector<pii> ends;
    for(const pii p : longList) {
        int i = p.S;
        if(diagonal[i] != currDiag) {
            sort(ends.begin(), ends.end());
            sort(inDiag.begin(), inDiag.end());
            F0R(j, inDiag.size()) endPos[inDiag[j].S] = MP(ends[j].F, -ends[j].S);
            currDiag = diagonal[i];
            inDiag.clear();
            ends.clear();
        }
        inDiag.PB(MP(positions[i].F, i));
        ends.PB(MP(endPos[i].F, -endPos[i].S));
    }
    sort(ends.begin(), ends.end());
    sort(inDiag.begin(), inDiag.end());
    F0R(j, inDiag.size()) endPos[inDiag[j].S] = MP(ends[j].F, -ends[j].S);
    F0R(i, n) cout << endPos[i].F << " " << endPos[i].S << "\n";
    return 0;
}
