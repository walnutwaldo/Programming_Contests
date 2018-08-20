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
#define MAXN 200

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, power[MAXN], maxReach, currReach;
pii cows[MAXN];
bool seen[MAXN];

double dis(int cow1, int cow2) {
    return sqrt(SQ(cows[cow1].F - cows[cow2].F) + SQ(cows[cow1].S - cows[cow2].S));
}

void dfs(int cowID) {
    currReach++;
    seen[cowID] = true;
    F0R(nextCow, n) if(cowID != nextCow && !seen[nextCow] && dis(cowID, nextCow) <= power[cowID]) dfs(nextCow);
}

int main() {
    ifstream fin("moocast.in");
    ofstream fout("moocast.out");

    fin >> n;
    F0R(i, n) {
        int x, y, p;
        fin >> cows[i].F >> cows[i].S >> power[i];
    }
    int maxReach = 0;
    F0R(i, n) {
        currReach = 0;
        memset(seen, 0, sizeof(bool) * MAXN);
        dfs(i);
        maxReach = max(maxReach, currReach);
    }
    fout << maxReach << endl;
    return 0;
}
