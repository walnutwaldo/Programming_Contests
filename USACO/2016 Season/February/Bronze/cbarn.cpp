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
#define MAXN 1000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, r[MAXN];

int main() {
    ifstream fin("cbarn.in");
    ofstream fout("cbarn.out");
    fin >> n;
    F0R(i, n) fin >> r[i];
    int minTravel = INT_MAX;
    F0R(i, n) {
        int cTravel = 0;
        F0R(j, n) {
            int dis = (j + n - i) % n;
            cTravel += r[j] * dis;
        }
        minTravel = min(minTravel, cTravel);
    }
    fout << minTravel << "\n";
    return 0;
}
