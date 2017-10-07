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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n, k;
int numBelow[10001];

int main() {
    ifstream fin("diamond.in");
    ofstream fout("diamond.out");
    fin >> n >> k;
    F0R(i, n) {
        int a;
        fin >> a;
        numBelow[a]++;
    }
    FOR(i, 1, 10001) numBelow[i] += numBelow[i - 1];
    int res = numBelow[k];
    FOR(i, k + 1, 10001) res = max(res, numBelow[i] - numBelow[i - k - 1]);
    fout << res << "\n";
    return 0;
}
