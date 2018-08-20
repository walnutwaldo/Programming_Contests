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

int N;
ll workNeeded[MAXN], K;

ld timeNeeded(ld b) {
    ld time = 0;
    ll cowsUsed = 0;
    F0R(i, N) {
        ll cowsOnThisFloor = (ll)((1+sqrt(1+(ld)workNeeded[i]*4/b))/2);
        time += (ld)workNeeded[i] / cowsOnThisFloor;
        cowsUsed += cowsOnThisFloor;
    }
    time += b * (cowsUsed - K);
    return time;
}

ll countCowsUsed(ld b) {
    ll res = 0;
    F0R(i, N) {
        res += (ll)((1+sqrt(1+(ld)workNeeded[i]*4/b))/2);
    }
    return res;
}

int main() {
    ifstream fin("tallbarn.in");
    ofstream fout("tallbarn.out");

    fin >> N >> K;
    ld lo = 0, hi = 0;
    F0R(i, N) {
        fin >> workNeeded[i];
        hi = (ld)max((ll)hi, workNeeded[i]);
    }
    F0R(counter, 200) {
        ld mid = (lo + hi)/2;
        if(countCowsUsed(mid) >= K) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    fout << (ll)round(timeNeeded(lo));
    return 0;
}
