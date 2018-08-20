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
#define MAXN 100

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n, x[MAXN], side[MAXN];

int main() {
    ifstream fin("hoofball.in");
    ofstream fout("hoofball.out");
    fin >> n;
    if(n == 1)
        fout << 1 << endl;
    else {
        F0R(i, n) fin >> x[i];
        sort(x, x + n);
        F0R(i, n) {
            if(i == 0)
                side[i] = 1;
            else if(i == n - 1)
                side[i] = -1;
            else
                side[i] = (x[i + 1] - x[i] < x[i] - x[i - 1])? 1 : -1;
        }
        int res = 0;
        F0R(i, n) {
            if((i == 0 || side[i - 1] == -1) && (i == n - 1 || side[i + 1] == 1)) res++;
            else if((i == 0 || side[i - 1] == -1) && i < n - 1 && side[i + 1] == -1 && (i == n - 2 || side[i + 2] == 1) && side[i] == 1) res++;
        }
        fout << res << endl;
    }
    return 0;
}
