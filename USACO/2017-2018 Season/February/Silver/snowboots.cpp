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
#define MAXN 250

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n, b;
ll depth[MAXN];
pair<ll, int> boots[MAXN];
bool possible[MAXN];

int main() {
    ifstream fin("snowboots.in");
    ofstream fout("snowboots.out");
    fin >> n >> b;
    F0R(i, n) fin >> depth[i];
    F0R(i, b) {
        ll s;
        int d;
        fin >> s >> d;
        boots[i] = MP(s, d);
    }
    possible[0] = 1;
    F0R(i, b) {
        F0R(j, n)
            if(possible[j] && depth[j] <= boots[i].F)
                F0R(k, boots[i].S + 1) if(j + k < n && depth[j + k] <= boots[i].F)
                    possible[j + k] = 1;
        if(possible[n - 1]) {
            fout << i << endl;
            break;
        }
    }
    return 0;
}
