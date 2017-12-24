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
#define MAXN 100

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, a[MAXN], start[MAXN];

int main() {
    ifstream fin("shuffle.in");
    ofstream fout("shuffle.out");
    fin >> n;
    F0R(i, n) {
        int b;
        fin >> b;
        b--;
        a[b] = i;
    }
    F0R(i, n) {
        int x;
        fin >> x;
        start[a[a[a[i]]]] = x;
    }
    F0R(i, n) fout << start[i] << "\n";
    return 0;
}
