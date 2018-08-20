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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n;
ll k;
ll sizes[50000];

int main() {
    ifstream fin("diamond.in");
    ofstream fout("diamond.out");
    fin >> n >> k;
    F0R(i, n) fin >> sizes[i];
    sort(sizes, sizes + n);
    int preBest[n], postBest[n];
    preBest[0] = 1;
    postBest[n - 1] = 1;
    FOR(i, 1, n) {
        int j = LB(sizes, sizes + n, sizes[i] - k) - sizes;
        preBest[i] = max(preBest[i - 1], i - j + 1);
    }
    R0F(i, n - 1) {
        int j = UB(sizes, sizes + n, sizes[i] + k) - sizes;
        postBest[i] = max(postBest[i + 1], j - i);
    }
    int res = 0;
    F0R(i, n - 1) res = max(res, preBest[i] + postBest[i + 1]);
    fout << res << "\n";
    return 0;
}
