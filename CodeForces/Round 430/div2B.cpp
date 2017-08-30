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

int r, d, n;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> r >> d >> n;
    int res = 0;
    F0R(i, n) {
        int x, y, ri;
        cin >> x >> y >> ri;
        point sausage(x, y);
        double dis = abs(sausage);
        int lo = r - d + ri;
        int hi = r - ri;
        if(dis >= lo && dis <= hi) res++;
    }
    cout << res << endl;
    return 0;
}
close
