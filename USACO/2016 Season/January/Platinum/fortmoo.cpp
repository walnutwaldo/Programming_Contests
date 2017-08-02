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
#define MAXN 200

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int h, w;
int lChain[MAXN][MAXN], uChain[MAXN][MAXN];

int main() {
    ifstream fin("fortmoo.in");
    ofstream fout("fortmoo.out");
    fin >> h >> w;
    F0R(i, h) F0R(j, w) {
        char c;
        fin >> c;
        if(j > 0 && c == '.') {
            lChain[j][i] = lChain[j - 1][i];
        }
        if(i > 0 && c == '.') {
            uChain[j][i] = uChain[j][i - 1];
        }
        if(c =='.') {
            lChain[j][i]++;
            uChain[j][i]++;
        }
    }
    int maxArea = 0;
    F0R(y2, h) F0R(x2, w) {
        if(lChain[x2][y2] == 0) continue;
        FOR(width, 1, lChain[x2][y2] + 1) {
            ROF(height, 1, min(uChain[x2][y2], uChain[x2 - width + 1][y2]) + 1) {
                if(lChain[x2][y2 - height + 1] >= width) {
                    maxArea = max(maxArea, width * height);
                    break;
                }
            }
        }
    }
    fout << maxArea << "\n";
    return 0;
}
