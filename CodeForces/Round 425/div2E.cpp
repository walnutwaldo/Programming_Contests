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
#define PRIME 17
#define MOD 1000000007
#define MAXN 500

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ll> point;

int n, m, q;
int mat[MAXN][MAXN];
int application[MAXN][MAXN];
bool emptyVector[MAXN];
int inv5[5] {0, 1, 3, 2, 4};
int vec[MAXN];
int valMult[MAXN];
ll pow5[MAXN + 1];

ll getPow(int p) {
    if(pow5[p] != -1) return pow5[p];
    if(p == 0) pow5[p] = 1;
    else if(p == 1) pow5[p] = 5;
    else pow5[p] = (getPow(p / 2) * getPow((p + 1) / 2)) % MOD;
    return pow5[p];
}

int getRank() {
    int r = 0;
    F0R(i, m) {
        if(emptyVector[i] && vec[i]) return -1;
        if(emptyVector[i]) continue;
        r++;
        vec[i] = (vec[i] * valMult[i]) % 5;
        FOR(row2, i + 1, m) vec[row2] = (vec[row2] + application[row2][i] * vec[i]) % 5;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    F0R(i, n) F0R(j, m) {
        char c;
        cin >> c;
        mat[j][i] = c - 'a';
    }
    F0R(row, m) {
        int firstSpot = -1;
        F0R(col, n) if(mat[row][col] != 0) {
            firstSpot = col;
            break;
        }
        if(firstSpot == -1) {
            emptyVector[row] = true;
            continue;
        }
        int val = mat[row][firstSpot];
        valMult[row] = inv5[val];
        F0R(col, n) mat[row][col] = (mat[row][col] * inv5[val]) % 5;
        FOR(row2, row + 1, m) {
            int mult = 4 * mat[row2][firstSpot];
            application[row2][row] = mult;
            F0R(col, n) mat[row2][col] = (mat[row2][col] + application[row2][row] * mat[row][col]) % 5;
        }
    }
    F0R(i, MAXN + 1) pow5[i] = -1;
    cin >> q;
    F0R(i, q) {
        F0R(j, m) {
            char c;
            cin >> c;
            vec[j] = c - 'a';
        }
        int r = getRank();
        if(r == -1) cout << "0\n";
        else cout << getPow(n - r) << "\n";
    }
    return 0;
}
