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

int k, sum;
string n;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> k >> n;
    sort(n.begin(), n.end());
    F0R(i, n.size()) {
        sum += (int)(n[i] - '0');
    }
    int d = k - sum;
    int i = 0;
    while(d > 0) {
        d -= (int)('9' - n[i]);
        i++;
    }
    cout << i << "\n";
    return 0;
}
