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
#define MAXN 5000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n;
ll a[MAXN + 1], prefix[MAXN + 1];
tuple<ll, int, int> maxSegment[MAXN + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    F0R(i, n) cin >> a[i];
    F0R(i, n) prefix[i + 1] = a[i];
    FOR(i, 1, n + 1) prefix[i] += prefix[i - 1];
    F0R(i, n + 1) maxSegment[i] = MT(0, i, i);
    F0R(a, n + 1) FOR(b, a, n + 1) {
        ll curr = prefix[b] - prefix[a];
        maxSegment[a] = max(maxSegment[a], MT(curr, a, b));
    }
    R0F(i, n) maxSegment[i] = max(maxSegment[i], maxSegment[i + 1]);
    int a = -1, b, c;
    F0R(i, n) {
        ll curr = 2 * (prefix[i] + get<0>(maxSegment[i])) - prefix[n];
        if(a == -1 || curr > 2 * prefix[c] - 2 * prefix[b] + 2 * prefix[a] - prefix[n]) {
            a = i;
            b = get<1>(maxSegment[i]);
            c = get<2>(maxSegment[i]);
        }
    }
    cout << a << " " << b << " " << c << "\n";
    return 0;
}
