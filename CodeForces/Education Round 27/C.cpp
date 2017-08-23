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
#define X real()
#define Y imag()
#define MAXM 200000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ll> point;

int m;
ll A[MAXM], B[MAXM], Aprime[MAXM];
pii C[MAXM];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> m;
    F0R(i, m) cin >> A[i];
    F0R(i, m) cin >> B[i];
    F0R(i, m) {
        C[i] = MP(B[i], i);
    }
    sort(A, A + m);
    sort(C, C + m);
    F0R(i, m) {
        Aprime[C[i].S] = A[m - i - 1];
    }
    F0R(i, m) cout << Aprime[i] << " ";
    cout << "\n";
    return 0;
}
