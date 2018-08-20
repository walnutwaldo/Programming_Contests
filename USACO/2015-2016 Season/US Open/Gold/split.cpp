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
#define MAXN 50000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n;
ll res = 0, start;
pair<ll, ll> cows[MAXN];

void solve() {
    sort(cows, cows + n);
    ll maxY1[n], minY1[n], minY2[n], maxY2[n];
    maxY1[0] = cows[0].S;
    minY1[0] = cows[0].S;
    maxY2[n - 1] = cows[n - 1].S;
    minY2[n - 1] = cows[n - 1].S;
    FOR(i, 1, n) {
        maxY1[i] = max(maxY1[i - 1], cows[i].S);
        minY1[i] = min(minY1[i - 1], cows[i].S);
    }
    R0F(i, n - 1) {
        maxY2[i] = max(maxY2[i + 1], cows[i].S);
        minY2[i] = min(minY2[i + 1], cows[i].S);
    }
    R0F(i, n - 1) {
        ll area1 = (cows[i].F - cows[0].F) * (maxY1[i] - minY1[i]);
        ll area2 = (cows[n - 1].F - cows[i + 1].F) * (maxY2[i + 1] - minY2[i + 1]);
        res = max(res, start - area1 - area2);
    }
}

int main() {
    ifstream fin("split.in");
    ofstream fout("split.out");
    fin >> n;
    ll minX = -1, maxX = 0, minY = -1, maxY = 0;
    F0R(i, n) {
        ll x, y;
        fin >> x >> y;
        cows[i] = MP(x, y);
        if(minX == -1 || x < minX) minX = x;
        if(minY == -1 || y < minY) minY = y;
        maxX = max(maxX, x);
        maxY = max(maxY, y);
    }
    start = (maxX - minX) * (maxY - minY);
    solve();
    F0R(i, n) swap(cows[i].F, cows[i].S);
    solve();
    fout << res << "\n";
    return 0;
}
