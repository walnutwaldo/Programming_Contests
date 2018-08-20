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
#define MAXN 50000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n;
bool inE[MAXN * 2];

int main() {
    ifstream fin("highcard.in");
    ofstream fout("highcard.out");
    fin >> n;
    F0R(i, n) {
        int cardNum;
        fin >> cardNum;
        inE[cardNum - 1] = true;
    }
    int numUnbeaten = 0;
    int numWins = 0;
    F0R(i, 2 * n) {
        if(inE[i]) numUnbeaten++;
        if(!inE[i])
            if(numUnbeaten > 0) {
                numWins++;
                numUnbeaten--;
            }
    }
    fout << numWins << "\n";
    return 0;
}
