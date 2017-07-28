#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (a) - 1; i >= (b); i--)

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define MAXN 100000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, q, bcount[3][MAXN + 1];

int main() {
    ifstream fin("bcount.in");
    ofstream fout("bcount.out");
    fin >> n >> q;
    FOR(i, 1, n + 1) {
        F0R(j, 3) bcount[j][i] = bcount[j][i - 1];
        int b;
        fin >> b;
        bcount[--b][i]++;
    }
    F0R(i, q) {
        int a, b;
        fin >> a >> b;
        fout << bcount[0][b] - bcount[0][a - 1] << " " << bcount[1][b] - bcount[1][a - 1] << " " << bcount[2][b] - bcount[2][a - 1] << "\n";
    }
    return 0;
}
