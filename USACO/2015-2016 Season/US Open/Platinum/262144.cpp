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
#define MAXN 262144

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n, ending[60][MAXN + 1];

int main() {
    ifstream fin("262144.in");
    ofstream fout("262144.out");
    fin >> n;
    F0R(i, 60) F0R(j, n + 1) ending[i][j] = -1;
    F0R(i, n) {
        int a;
        fin >> a;
        ending[a][i] = i;
    }
    int res = 0;
    F0R(i, 60) {
        F0R(j, n) {
            if(ending[i][j] != -1) {
                res = max(res, i);
                if(ending[i][ending[i][j] + 1] != -1) {
                    ending[i + 1][j] = ending[i][ending[i][j] + 1];
                }
            }
        }
    }
    fout << res << "\n";
    return 0;
}
