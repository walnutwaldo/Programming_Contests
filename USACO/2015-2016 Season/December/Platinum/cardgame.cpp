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
#define MAXN 50000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n;
bool inE[MAXN * 2];
vi e, b;
int points[1 << 18], unbeaten[1 << 18], unused[1 << 18];

void update(int n) {
    while(n > 1) {
        int parent = n / 2;
        int newPoints = min(unused[parent * 2 + 1], unbeaten[parent * 2]);
        points[parent] = points[parent * 2] + points[parent * 2 + 1] + newPoints;
        unbeaten[parent] = unbeaten[2 * parent] + unbeaten[2 * parent + 1] - newPoints;
        unused[parent] = unused[2 * parent + 1] + unused[2 * parent] - newPoints;
        n = parent;
    }
}

vi solve() {
    memset(points, 0, sizeof(int) * (1 << 18));
    memset(unbeaten, 0, sizeof(int) * (1 << 18));
    memset(unused, 0, sizeof(int) * (1 << 18));
    vi res;
    res.PB(0);
    F0R(i, n) {
        unbeaten[(1 << 17) + e[i]]++;
        unused[(1 << 17) + b[i]]++;
        update((1 << 17) + e[i]);
        update((1 << 17) + b[i]);
        res.PB(points[1]);
    }
    return res;
}

int main() {
    ifstream fin("cardgame.in");
    ofstream fout("cardgame.out");
    fin >> n;
    F0R(i, n) {
        int cardNum;
        fin >> cardNum;
        e.PB(--cardNum);
        inE[e[i]] = true;
    }
    R0F(i, 2 * n) if(!inE[i]) b.PB(i);
    vi highWin = solve();
    F0R(i, n) {
        e[i] = 2 * n - 1 - e[i];
        b[i] = 2 * n - 1 - b[i];
    }
    reverse(e.begin(), e.end());
    reverse(b.begin(), b.end());
    vi lowWin = solve();
    int res = 0;
    F0R(i, n + 1) res = max(res, lowWin[n - i] + highWin[i]);
    fout << res << "\n";
    return 0;
}
