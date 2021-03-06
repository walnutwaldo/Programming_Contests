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

#define MAXN 18

int n;
set<string> res, f[MAXN], b[MAXN];
char a[MAXN][MAXN];

void solve(ll steps, int left) {
    if(!left) {
        string s1, s2;
        int r1 = 0, c1 = 0, r2 = n - 1, c2 = n - 1;
        s1 += a[r1][c1], s2 += a[r2][c2];
        F0R(i, n - 1) {
            if(steps & (1LL << i)) r1++, r2--;
            else c1++, c2--;
            s1 += a[r1][c1];
            s2 += a[r2][c2];
        }
        f[r1].insert(s1);
        b[r2].insert(s2);
    }
    if(left) {
        solve(steps | (1LL << (n - 1 - left)), left - 1);
        solve(steps, left - 1);
    }
}

int main() {
    ifstream fin("palpath.in");
    ofstream fout("palpath.out");
    fin >> n;
    F0R(i, n) F0R(j, n) fin >> a[i][j];
    solve(0, n - 1);
    F0R(i, n) for(auto s : f[i]) if(b[i].count(s)) res.insert(s);
    fout << sz(res) << endl;
}
