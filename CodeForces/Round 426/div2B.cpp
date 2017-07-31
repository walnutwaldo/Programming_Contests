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
#define MAXN 1000000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int first[26], last[26], n, k;
int gate[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    F0R(i, 26) {
        first[i] = -1;
        last[i] = -1;
    }
    F0R(i, n) {
        char c;
        cin >> c;
        if(first[c - 'A'] == -1) {
            first[c - 'A'] = i;
        }
        last[c - 'A'] = i;
        gate[i] = c - 'A';
    }
    int numOn = 0;
    bool on[26];
    memset(on, 0, 26 * sizeof(bool));
    F0R(i, n) {
        if(!on[gate[i]]) {
            numOn++;
            on[gate[i]] = true;
        }
        if(numOn > k) {
            cout << "YES\n";
            return 0;
        }
        if(i == last[gate[i]]) {
            on[gate[i]] = false;
            numOn--;
        }
    }
    cout << "NO\n";
    return 0;
}
