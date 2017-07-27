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
#define MAXN 500
#define MAXM 50
#define MAXV 64

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, m;
string genes[2 * MAXN];
bool has[MAXM][MAXM][MAXM][MAXV], notPossible[MAXM][MAXM][MAXM];

int valOf(char c) {
    int v = 0;
    switch(c) {
    case 'T':
        v += 1;
    case 'C':
        v += 1;
    case 'A':
        v += 1;
    }
    return v;
}

int valOf(char a, char b, char c) {
    return 16 * valOf(a) + 4 * valOf(b) + valOf(c);
}

int main() {
    ifstream fin("cownomics.in");
    ofstream fout("cownomics.out");
    fin >> n >> m;
    F0R(i, 2 * n) fin >> genes[i];
    F0R(i, n) F0R(a, m) FOR(b, a + 1, m) FOR(c, b + 1, m) has[a][b][c][valOf(genes[i][a], genes[i][b], genes[i][c])] = true;
    FOR(i, n, 2 * n) F0R(a, m) FOR(b, a + 1, m) FOR(c, b + 1, m) if(has[a][b][c][valOf(genes[i][a], genes[i][b], genes[i][c])]) notPossible[a][b][c] = true;
    int res = 0;
    F0R(a, m) FOR(b, a + 1, m) FOR(c, b + 1, m) if(!notPossible[a][b][c]) res++;
    fout << res << endl;
    return 0;
}
