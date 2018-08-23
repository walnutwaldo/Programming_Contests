#include <bits/stdc++.h>

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define ran() (rand() & 0x7FFF)
#define rand31() ((ran() << 16) | (ran() << 1) | (ran() & 1))
#define rand32() ((ran() << 17) | (ran() << 2) | (ran() & 3))
#define rand63() (((ll)ran() << 48) | ((ll)ran() << 33) | ((ll)ran() << 18) | ((ll)ran() << 3) | ((ll)ran() & 7))
#define rand64() (((ll)ran() << 49) | ((ll)ran() << 34) | ((ll)ran() << 19) | ((ll)ran() << 4) | ((ll)ran() & 15))

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define X real()
#define Y imag()

#define PI acos(-1)

#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define SQ(x) ((x) * (x))

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef vector<ll> vll;
typedef vector<ull> vul;
typedef complex<ld> point;
typedef complex<ld> cld;
typedef vector<cld> vcld;

#define MAXN 500

int n, m;
char a[MAXN][MAXN];

int cnt(char M, char O) {
    int res = 0;
    F0R(i, n) F0R(j, m - 2) if(a[i][j] == M && a[i][j + 1] == O && a[i][j + 2] == O) res++;
    F0R(i, n) F0R(j, m - 2) if(a[i][j] == O && a[i][j + 1] == O && a[i][j + 2] == M) res++;
    F0R(i, n - 2) F0R(j, m) if(a[i][j] == M && a[i + 1][j] == O&& a[i + 2][j] == O) res++;
    F0R(i, n - 2) F0R(j, m) if(a[i][j] == O && a[i + 1][j] == O && a[i + 2][j] == M) res++;
    F0R(i, n - 2) F0R(j, m - 2) if(a[i][j] == O && a[i + 1][j + 1] == O && a[i + 2][j + 2] == M) res++;
    F0R(i, n - 2) F0R(j, m - 2) if(a[i][j] == M && a[i + 1][j + 1] == O && a[i + 2][j + 2] == O) res++;
    F0R(i, n - 2) F0R(j, m - 2) if(a[i][j + 2] == O && a[i + 1][j + 1] == O && a[i + 2][j] == M) res++;
    F0R(i, n - 2) F0R(j, m - 2) if(a[i][j + 2] == M && a[i + 1][j + 1] == O && a[i + 2][j] == O) res++;
    return res;
}

int main() {
	ifstream fin("moocrypt.in");
	ofstream fout("moocrypt.out");
    fin >> n >> m;
    F0R(i, n) F0R(j, m) fin >> a[i][j];
    int res = 0;
    F0R(M, 26) F0R(O, 26) if(M != O && (M + 'A') != 'M' && (O + 'A') != 'O') res = max(res, cnt('A' + M, 'A' + O));
    fout << res << endl;
}
