#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

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
#define MAX 100000

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;
typedef complex<ld> cld;

int N, M, R, c[MAX];
ll r[MAX];
pair<ll, int> stores[MAX];

int main() {
    ifstream fin("rental.in");
    ofstream fout("rental.out");
    fin >> N >> M >> R;
    F0R(i, N) fin >> c[i];
    F0R(i, M) fin >> stores[i].S >> stores[i].F;
    F0R(i, R) fin >> r[i];
    sort(c, c + N, greater<int>());
    sort(stores, stores + M, greater<pair<ll, int>>());
    sort(r, r + R, greater<ll>());
    R = min(R, N);
    ll curr = 0, res;
    int currStore = 0, currCow = 0, currFree = 0;
    F0R(i, N - R) currFree += c[currCow++];
    F0R(i, R) curr += r[i];
    while(currStore < M && currFree) {
        int dec = min(stores[currStore].S, currFree);
        currFree -= dec;
        curr += stores[currStore].F * dec;
        stores[currStore].S -= dec;
        if(stores[currStore].S == 0) currStore++;
    }
    res = curr;
    R0F(i, R) {
        curr -= r[i];
        currFree += c[currCow++];
        while(currStore < M && currFree) {
            int dec = min(stores[currStore].S, currFree);
            currFree -= dec;
            curr += stores[currStore].F * dec;
            stores[currStore].S -= dec;
            if(stores[currStore].S == 0) currStore++;
        }
        res = max(res, curr);
    }
    fout << res << endl;
    return 0;
}
