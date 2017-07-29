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
#define MAXN 100

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n;
int bales[MAXN];

int rightEnd(int i, int x) {
    int next = UB(bales, bales + n, bales[i] + x) - bales - 1;
    if(next > i) return rightEnd(next, x + 1);
    return i;
}

int leftEnd(int i, int x) {
    int next = LB(bales, bales + n, bales[i] - x) - bales;
    if(next < i) return leftEnd(next, x + 1);
    return i;
}

int main() {
    ifstream fin("angry.in");
    ofstream fout("angry.out");
    fin >> n;
    F0R(i, n) fin >> bales[i];
    sort(bales, bales + n);
    int res = 0;
    F0R(i, n)  res = max(res, rightEnd(i, 1) - leftEnd(i, 1) + 1);
    fout << res << "\n";
    return 0;
}
