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
#define UB upper_bound
#define MAXN 100000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;

int N, K;
vll diff[MAXN];
ll baseCost, maxExtra, numRobots, savings, firstDiff[MAXN];

void countRobots(int location, ll budget) {
    if(numRobots>=K)
        return;
    if(location != -1 && budget < diff[location][0])
        location = UB(firstDiff, firstDiff + location, budget) - firstDiff - 1;
    if(location == -1) {
        numRobots++;
        return;
    }
    countRobots(location - 1, budget);
    for(int i = 0; i < diff[location].size() && diff[location][i] <= budget; i++) {
        countRobots(location - 1, budget - diff[location][i]);
    }
}

void countSavings(int location, ll budget) {
    if(location != -1 && budget < diff[location][0])
        location = UB(firstDiff, firstDiff + location, budget) - firstDiff - 1;
    if(location == -1) {
        savings += budget + 1;
        return;
    }
    countSavings(location - 1,budget);
    for(int i = 0; i < diff[location].size() && diff[location][i] <= budget; i++) {
        countSavings(location - 1, budget - diff[location][i]);
    }
}

int main() {

    ifstream fin("roboherd.in");
    ofstream fout("roboherd.out");

    fin >> N >> K;

    F0R(i, N) {
        ll M;
        fin >> M;
        vll v;
        F0R(j, M) {
            ll x;
            fin >> x;
            v.PB(x);
        }
        sort(v.begin(), v.end());
        baseCost+=v[0];
        if(M == 1) {
            N--;
            i--;
            continue;
        }
        FOR(j, 1, M) {
            diff[i].PB(v[j]-v[0]);
        }
        maxExtra+=diff[i].back();
    }
    sort(diff, diff + N);
    F0R(i, N) {
        firstDiff[i] = (diff[i][0]);
    }

    ll lo = 0, hi = maxExtra;
    while(lo < hi) {
        ll mid = (lo+hi)/2;
        numRobots = 0;
        countRobots(N - 1, mid);
        if(numRobots >= K) {
            hi = mid;
        } else {
            lo = mid+1;
        }
    }

    if(lo > 0)
        countSavings(N - 1, lo - 1);

    fout << (baseCost + lo) * K - savings << endl;

    return 0;
}
