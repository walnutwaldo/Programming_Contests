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
#define MAXM 1000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int x, y, m;
bool possible[MAXM + 1];

int main() {
    ifstream fin("pails.in");
    ofstream fout("pails.out");
    fin >> x >> y >> m;
    possible[0] = true;
    int maxPossible = 0;
    F0R(i, m + 1) {
        if(possible[i]) {
            maxPossible = i;
            if(i + x <= m) possible[i + x] = true;
            if(i + y <= m) possible[i + y] = true;
        }
    }
    fout << maxPossible << "\n";
    return 0;
}
