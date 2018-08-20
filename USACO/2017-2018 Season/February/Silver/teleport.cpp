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
#define MAXN 100000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n, a[MAXN], b[MAXN];
vector<pair<ll, int>> toProcess;
ll curr;

int main() {
    ifstream fin("teleport.in");
    ofstream fout("teleport.out");
    fin >> n;
    F0R(i, n) {
        ll a, b;
        fin >> a >> b;
        curr += abs(a - b);
        if(abs(a) < abs(a - b)) {
            toProcess.PB(MP(b - abs(a - b) + abs(a), -1));
            toProcess.PB(MP(b, 2));
            toProcess.PB(MP(b + abs(a - b) - abs(a), -1));
        }
    }
    sort(toProcess.begin(), toProcess.end());
    ll res = curr;
    ll currInc = 0, lastSpot = INT_MIN;
    for(const pair<ll, int> p : toProcess) {
        curr += currInc * (p.F - lastSpot);
        currInc += p.S;
        lastSpot = p.F;
        res = min(res, curr);
    }
    fout << res << endl;
    return 0;
}
