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
    int pairsHave = 2 * n;
    int foursHave = n;

    int pairsNeeded = 0;
    int foursNeeded = 0;
    int singlesNeeded = 0;

    F0R(i, k) {
        int numSoldiers;
        cin >> numSoldiers;
        foursNeeded += numSoldiers / 4;
        numSoldiers %= 4;
        if(numSoldiers >= 2) pairsNeeded++;
        if(numSoldiers % 2 == 1) singlesNeeded++;
    }
    int foursUsed = min(singlesNeeded, pairsNeeded);
    foursUsed = min(foursUsed, foursHave);
    foursHave -= foursUsed;
    pairsNeeded -= foursUsed;
    singlesNeeded -= foursUsed;

    foursUsed = min(singlesNeeded / 2, foursHave);
    foursHave -= foursUsed;
    singlesNeeded -= 2 * foursUsed;

    foursUsed = min(foursHave, foursNeeded);
    foursNeeded -= foursUsed;
    foursHave -= foursUsed;

    foursUsed = 2 * min(foursHave/2, pairsNeeded / 3);
    pairsNeeded -= 3 * foursUsed / 2;
    foursHave -= foursUsed;

    pairsHave += foursHave;
    pairsNeeded += 2 * foursNeeded;
    pairsNeeded += singlesNeeded;
    if(pairsNeeded <= pairsHave) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}
