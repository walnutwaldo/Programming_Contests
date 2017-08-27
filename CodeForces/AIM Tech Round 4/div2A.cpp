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

string s;
int n;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> s;
    cin >> n;
    if(n > s.size() || n > 26) {
        cout << "impossible\n";
        return 0;
    }
    set<char> se;
    for(const char c : s) se.insert(c);
    cout << max(0, (int)(n - se.size())) << "\n";
    return 0;
}
