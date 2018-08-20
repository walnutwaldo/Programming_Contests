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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int x[6], y[6];

int main() {
    ifstream fin("billboard.in");
    ofstream fout("billboard.out");
    F0R(i, 6) fin >> x[i] >> y[i];
    int area = 0;
    F0R(i, 2) {
        area += (x[2 * i + 1] - x[2 * i]) * (y[2 * i + 1] - y[2 * i]);
        int x1 = max(x[2 * i], x[4]);
        int x2 = min(x[2 * i + 1], x[5]);
        int y1 = max(y[2 * i], y[4]);
        int y2 = min(y[2 * i + 1], y[5]);
        area -= max(0, x2 - x1) * max(0, y2 - y1);
    }
    fout << area;
    return 0;
}
