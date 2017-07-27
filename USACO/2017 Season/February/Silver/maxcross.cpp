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
#define MAXN 100000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int N, K, B, needToFix[MAXN];
bool broken[MAXN];

int main() {
    ifstream fin("maxcross.in");
    ofstream fout("maxcross.out");

    fin >> N >> K >> B;

    F0R(i, B) {
        int brokenSign;
        fin >> brokenSign;
        broken[brokenSign - 1] = 1;
    }
    int minimumFix = B;
    F0R(i, N) {
        int base = 0;
        if(i > 0) base = needToFix[i - 1];
        base += broken[i];
        if(i >= K) base -= broken[i - K];
        needToFix[i] = base;
        if(i >= K - 1) minimumFix = min(minimumFix, needToFix[i]);
    }
    fout << minimumFix;
    return 0;
}
