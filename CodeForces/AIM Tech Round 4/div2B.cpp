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
#define MAXN 50

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ll> point;

int n, m, num;
int colorOfSquare[MAXN][MAXN];
ll answer;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    F0R(r, n) F0R(c, m) cin >> colorOfSquare[r][c];
    F0R(r, n) {
        int curr = 0;
        F0R(c, m) {
            curr += colorOfSquare[r][c];
        }
        answer += (((ll)1) << curr) - 1;
        answer += (((ll)1) << (m - curr)) - 1;
    }
    F0R(c, m) {
        int curr = 0;
        F0R(r, n) {
            curr += colorOfSquare[r][c];
        }
        answer += (((ll)1) << curr) - 1;
        answer += (((ll)1) << (n - curr)) - 1;
    }
    cout << answer - n * m << "\n";
    return 0;
}
