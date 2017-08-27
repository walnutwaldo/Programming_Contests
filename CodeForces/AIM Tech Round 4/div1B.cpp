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
typedef complex<ll> point;

int n, child[MAXN], start, lastBeforeX;;
ll val[MAXN];
ll x;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> start >> x;
    start--;
    lastBeforeX = start;
    F0R(i, n) val[i] = -1;
    F0R(i, 1000) {
        int qSpot = (int)floor((double)rand()/RAND_MAX * n);
        cout << "? " << qSpot + 1 << "\n";
        cout.flush();
        cin >> val[qSpot] >> child[qSpot];
        child[qSpot]--;
        if(val[qSpot] < x && (val[lastBeforeX] < val[qSpot])) {
            lastBeforeX = qSpot;
        }
    }
    int curr = lastBeforeX;
    while(curr != -2) {
        if(val[curr] == -1) {
            cout << "? " << curr + 1 << "\n";
            cout.flush();
            cin >> val[curr] >> child[curr];
            child[curr]--;
        }
        if(val[curr] >= x) break;
        else curr = child[curr];
    }
    if(curr == -2) cout << "! -1\n";
    else cout << "! " << val[curr] << "\n";
    return 0;
}
