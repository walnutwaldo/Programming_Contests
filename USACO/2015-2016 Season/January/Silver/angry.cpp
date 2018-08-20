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
#define MAXN 50000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, k;
ll bales[MAXN];

bool works(int r) {
    int i = 0;
    int cowsLeft = k;
    while(i < n && cowsLeft > 0) {
        i = UB(bales, bales + n, bales[i] +  2 * r) - bales;
        cowsLeft--;
    }
    if(i == n) return true;
    return false;
}

int main() {
    ifstream fin("angry.in");
    ofstream fout("angry.out");
    fin >> n >> k;
    F0R(i, n) fin >> bales[i];
    sort(bales, bales + n);
    ll lo = 1, hi = 1e9;
    while(lo < hi) {
        ll mid = (lo + hi) / 2;
        if(works(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    fout << lo << "\n";
    return 0;
}
