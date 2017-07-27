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
#define MAXM 100

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, m;
int spotted[MAXM], notSpotted[MAXM];

int valOf(char c) {
    int v = 1;
    switch(c) {
    case 'T':
        v <<= 1;
    case 'C':
        v <<= 1;
    case 'A':
        v <<= 1;
    }
    return v;
}

int main() {
    ifstream fin("cownomics.in");
    ofstream fout("cownomics.out");
    fin >> n >> m;
    F0R(i, n) F0R(j, m) {
            char c;
            fin >> c;
            spotted[j] |= valOf(c);
    }
    F0R(i, n) F0R(j, m) {
            char c;
            fin >> c;
            notSpotted[j] |= valOf(c);
    }
    int res = 0;
    F0R(i, m) if((spotted[i] & notSpotted[i]) == 0) res++;
    fout << res << endl;
    return 0;
}
