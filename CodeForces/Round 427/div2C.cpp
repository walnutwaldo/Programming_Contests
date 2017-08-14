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
typedef complex<ll> point;

int n, q, c;
int brightness[100][100][11];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q >> c;
    F0R(i, n) {
        int x, y, s;
        cin >> x >> y >> s;
        x--;
        y--;
        F0R(t, c + 1) {
            brightness[x][y][t] += s;
            s++;
            if(s > c) s = 0;
        }
    }
    F0R(x, 100) F0R(y, 100) F0R(t, c + 1) {
        if(x > 0) brightness[x][y][t] += brightness[x - 1][y][t];
        if(y > 0) brightness[x][y][t] += brightness[x][y - 1][t];
        if(x > 0 && y > 0) brightness[x][y][t] -= brightness[x - 1][y - 1][t];
    }
    F0R(i, q) {
        ll t;
        int x1, y1, x2, y2;
        cin >> t >> x1 >> y1 >> x2 >> y2;
        x1--;
        y1--;
        x2--;
        y2--;
        t %= (c + 1);
        int total = brightness[x2][y2][(int)t];
        if(x1 > 0) total -= brightness[x1 - 1][y2][(int)t];
        if(y1 > 0) total -= brightness[x2][y1 - 1][(int)t];
        if(x1 > 0 && y1 > 0) total += brightness[x1 - 1][y1 - 1][(int)t];
        cout << total << "\n";
    }
    return 0;
}
