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
#define MAXN 40

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, k, maxClique;
ll conn[MAXN];

void searchForClique(ll curr, int numInClique, int curNode) {
    if(curNode == n) maxClique = max(maxClique, numInClique);
    if(numInClique + n - curNode <= maxClique) return;
    if((conn[curNode] & curr) == curr) searchForClique(curr | ((ll)1 << curNode), numInClique + 1, curNode + 1);
    searchForClique(curr, numInClique, curNode + 1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    F0R(i, n) {
        conn[i] = 0;
        F0R(j, n) {
            ll c;
            cin >> c;
            conn[i] |= (c << j);
        }
    }
    searchForClique(0, 0, 0);
    cout << fixed << setprecision(9) << SQ((ld)k/maxClique) * maxClique * (maxClique - 1) / 2 << "\n";
    return 0;
}
