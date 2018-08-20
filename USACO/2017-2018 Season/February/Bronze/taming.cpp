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

int n, a[MAXN], minArr[MAXN];
bool isBreakout[MAXN], notBreakout[MAXN];

bool possible() {
    int lastBreakout = 0;
    isBreakout[0] = 1;
    F0R(i, n) if(a[i] != -1) {
        if(a[i] > i - lastBreakout || notBreakout[i - a[i]])
            return 0;
        else {
            lastBreakout = i - a[i];
            isBreakout[lastBreakout] = 1;
            FOR(k, lastBreakout + 1, i + 1) notBreakout[k] = 1;
        }
    }
    return 1;
}

int main() {
    ifstream fin("taming.in");
    ofstream fout("taming.out");
    fin >> n;
    F0R(i, n) fin >> a[i];
    if(!possible())
        fout << -1 << endl;
    else {
        int mn = 0, mx = 0;
        F0R(i, n) if(isBreakout[i]) mn++;
        F0R(i, n) if(!notBreakout[i]) mx++;
        fout << mn << " " << mx << endl;
    }
    return 0;
}
