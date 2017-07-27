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

int N, K, H[MAXN][21], P[MAXN][21], S[MAXN][21];
vector<char> moves;

int main() {
    ifstream fin("hps.in");
    ofstream fout("hps.out");

    fin >> N >> K;
    F0R(i, N) {
        char c;
        fin >> c;
        moves.PB(c);
    }

    F0R(i, N) {
        F0R(j, K+1) {
            if(i > 0) {
                H[i][j] = H[i-1][j];
                P[i][j] = P[i-1][j];
                S[i][j] = S[i-1][j];
            }
            if(j > 0) {
                H[i][j] = max(H[i][j], H[i][j-1]);
                P[i][j] = max(P[i][j], P[i][j-1]);
                S[i][j] = max(S[i][j], S[i][j-1]);
            }
            if(i > 0 && j > 0) {
                H[i][j] = max(H[i][j], max(P[i - 1][j - 1], S[i - 1][j - 1]));
                P[i][j] = max(P[i][j], max(H[i - 1][j - 1], S[i - 1][j - 1]));
                S[i][j] = max(S[i][j], max(P[i - 1][j - 1], H[i - 1][j - 1]));
            }
        }
        F0R(j, K+1)
        if(moves[i] == 'H') H[i][j]++;
        else if(moves[i] == 'P') P[i][j]++;
        else S[i][j]++;
    }
    fout << max(H[N-1][K], max(S[N-1][K],P[N-1][K]));
    return 0;
}
