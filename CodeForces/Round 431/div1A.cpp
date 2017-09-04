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
typedef complex<ld> point;

int k;
vi numOfChar;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> k;
    while(k > 0) {
        int minN = (int)floor((1 + sqrt(1 + 8 * k))/2);
        numOfChar.PB(minN);
        k-= minN * (minN - 1) / 2;
    }
    F0R(i, numOfChar.size()) F0R(j, numOfChar[i]) cout << (char)('a' + i);
    if(numOfChar.size() == 0) cout << "z";
    cout << "\n";
    return 0;
}
