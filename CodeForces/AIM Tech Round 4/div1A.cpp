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
#define MAXN 100000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ll> point;

int n;
ll a[MAXN];
bool inSub[MAXN];
unordered_map<ll, int> posOf;
vector<vi> subsequences;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    F0R(i, n) {
        cin >> a[i];
        posOf[a[i]] = i;
    }
    sort(a, a + n);
    F0R(i, n) {
        if(!inSub[i]) {
            vi v;
            int idx = i;
            while(!inSub[idx]) {
                v.PB(idx);
                inSub[idx] = true;
                idx = posOf[a[idx]];
            }
            subsequences.PB(v);
        }
    }
    cout << subsequences.size() << "\n";
    F0R(i, subsequences.size()) {
        cout << subsequences[i].size();
        F0R(j, subsequences[i].size()) cout << " " << subsequences[i][j] + 1;
        cout << "\n";
    }
    return 0;
}
