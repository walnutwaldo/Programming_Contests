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
#define MAXN 2000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

ll A, B, n, m, cOpen, rOpen;
ll lengthOfFence;
vi vertical, horizontal;

int main() {
    ifstream fin("fencedin.in");
    ofstream fout("fencedin.out");

    fin >> A >> B >> n >> m;
    vi verticalLocations, horizontalLocations;
    verticalLocations.PB(0);
    verticalLocations.PB(A);
    horizontalLocations.PB(0);
    horizontalLocations.PB(B);
    F0R(i, n) {
        int loc;
        fin >> loc;
        verticalLocations.PB(loc);
    }
    F0R(i, m) {
        int loc;
        fin >> loc;
        horizontalLocations.PB(loc);
    }
    sort(verticalLocations.begin(), verticalLocations.end());
    sort(horizontalLocations.begin(), horizontalLocations.end());
    F0R(i, n + 1) {
        horizontal.PB(verticalLocations[i + 1]-verticalLocations[i]);
    }
    F0R(i, m + 1) {
        vertical.PB(horizontalLocations[i + 1]-horizontalLocations[i]);
    }
    sort(horizontal.begin(), horizontal.end());
    sort(vertical.begin(), vertical.end());

    int i = 0, j = 0;
    while(i < vertical.size() || j < horizontal.size()) {
        if(j == horizontal.size() || (i < vertical.size() && vertical[i] < horizontal[j])) {
            if(rOpen == 0)
                lengthOfFence += n * vertical[i];
            else
                lengthOfFence += min(n, n + 1 - cOpen) * vertical[i];
            rOpen++;
            i++;
        } else {
            if(cOpen == 0)
                lengthOfFence += m * horizontal[j];
            else
                lengthOfFence += min(m, m + 1 - rOpen) * horizontal[j];
            cOpen++;
            j++;
        }
    }
    fout << lengthOfFence << endl;
    return 0;
}
