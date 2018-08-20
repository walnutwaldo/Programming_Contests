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
#define MAXN 100

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;
typedef complex<ld> cld;

int n;
pii shifts[MAXN];

int solve(int idx) {
    bool covered[1000];
    memset(covered, 0, 1000 * sizeof(bool));
    F0R(i, n) if(i != idx) FOR(j, shifts[i].F, shifts[i].S) covered[j] = 1;
    int res = 0;
    F0R(i, 1000) res += covered[i];
    return res;
}

int main() {
    ifstream fin("lifeguards.in");
    ofstream fout("lifeguards.out");
    fin >> n;
    F0R(i, n) fin >> shifts[i].F >> shifts[i].S;
    int res = 0;
    F0R(i, n) res = max(res, solve(i));
    fout << res << endl;
    return 0;
}
