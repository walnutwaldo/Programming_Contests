#include <bits/stdc++.h>

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define ran() (rand() & 0x7FFF)
#define rand31() ((ran() << 16) | (ran() << 1) | (ran() & 1))
#define rand32() ((ran() << 17) | (ran() << 2) | (ran() & 3))
#define rand63() (((ll)ran() << 48) | ((ll)ran() << 33) | ((ll)ran() << 18) | ((ll)ran() << 3) | ((ll)ran() & 7))
#define rand64() (((ll)ran() << 49) | ((ll)ran() << 34) | ((ll)ran() << 19) | ((ll)ran() << 4) | ((ll)ran() & 15))

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define X real()
#define Y imag()

#define INF 1e18
#define PI acos(-1)

#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define SQ(x) ((x) * (x))

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef vector<ll> vll;
typedef vector<ull> vul;
typedef complex<ld> point;
typedef complex<ld> cld;
typedef vector<cld> vcld;

#define MAXN 100000

struct BIT {

    int sz;
    int* tree;

    BIT(int _sz) {
        sz = _sz;
        tree = new int[sz + 1];
        memset(tree, 0, sizeof(int) * (sz + 1));
    }

    void update(int idx, int v) { for(idx++; idx <= sz; idx += idx & -idx) tree[idx] += v; }

    int query(int idx) {
        int res = 0;
        for(idx++; idx > 0; idx -= idx & -idx) res += tree[idx];
        return res;
    }

};

int n, arr[MAXN];

int main() {
    ifstream cin("sleepy.in");
    ofstream cout("sleepy.out");
    cin >> n;
    F0R(i, n) cin >> arr[i];
    int currSet = 0;
    BIT bit(n);
    R0F(i, n) {
        if(i == n -1 || arr[i] < arr[i + 1]) {
            currSet++;
            bit.update(arr[i] - 1, 1);
        } else break;
    }
    int res = n - currSet;
    cout << res << endl;
    F0R(i, res) {
        cout << n - currSet - 1 - i + bit.query(arr[i] - 1);
        if(i == res - 1) cout << "\n";
        else cout << " ";
        bit.update(arr[i] - 1, 1);
    }
}
