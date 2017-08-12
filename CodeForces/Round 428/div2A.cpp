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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, k;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    int total = 0;
    int given = 0;
    F0R(i, n) {
        int a;
        cin >> a;
        int togive = min(8, a + total);
        a-= togive;
        given+=togive;
        total+=a;
        if(given >= k) {
            cout << (i + 1) << endl;
            return 0;
        }
    }
    cout << "-1\n";
    return 0;
}
