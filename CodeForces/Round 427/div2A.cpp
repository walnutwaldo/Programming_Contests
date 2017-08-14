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

int s, v1, v2, t1, t2;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> s >> v1 >> v2 >> t1 >> t2;
    int total1 = s*v1 + 2 * t1;
    int total2 = s*v2 + 2 * t2;
    if(total1 < total2) cout << "First\n";
    else if(total1 > total2) cout << "Second\n";
    else cout << "Friendship\n";
    return 0;
}
