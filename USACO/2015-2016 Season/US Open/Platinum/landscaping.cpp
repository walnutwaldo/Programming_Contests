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
#define MAXN 100000
#define MAXPLOTS 1000000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, diff[MAXN];
ll x, y, z, disForLong;
vi inRow[MAXPLOTS];

ll* getMinPrefixArray(vi v) {
    ll* concCost = new ll[v.size() / 2 + 1];
    ll* minCost = new ll[v.size() / 2 + 1];
    ll* minCostLong = new ll[v.size() / 2 + 1];
    memset(concCost, 0, (v.size() / 2 + 1) * sizeof(ll));
    memset(minCost, 0, (v.size() / 2 + 1) * sizeof(ll));
    memset(minCost, 0, (v.size() / 2 + 1) * sizeof(ll));
    FOR(i, 1, v.size() / 2 + 1) {
        if(i > 1) concCost[i] = concCost[i - 1] + z * (v[2 * i - 2] - v[2 * i - 3]);
        int lb = 0;
        if(i > 1) lb = UB(v.begin(), v.end(), v[2 * i - 3] - disForLong) - v.begin();
        int ub = UB(v.begin(), v.end(), v[2 * i - 1] - disForLong) - v.begin();
        lb = (lb + 1) / 2;
        ub = (ub + 1) / 2;
        minCostLong[i] = 10000000000000000LL;
        FOR(j, lb, ub) {
            ll cost = x + y + concCost[i] - concCost[j + 1] + minCost[j];
            minCostLong[i] = min(minCostLong[i], cost);
        }
        if(i > 1) minCostLong[i] = min(minCostLong[i], minCostLong[i - 1] + z*(v[2 * i - 2] - v[2 * i - 3]));
        minCost[i] = min(minCost[i - 1] + z * (v[2 * i - 1] - v[2 * i - 2]), minCostLong[i]);
    }
    return minCost;
}

ll getMinCost(int row) {
    ll baseCost = 0;
    if(inRow[row].size() & 1) baseCost = (diff[inRow[row][0]] > 0) ? x : y;
    ll *prefix = getMinPrefixArray(inRow[row]);
    reverse(inRow[row].begin(), inRow[row].end());
    F0R(i, inRow[row].size()) inRow[row][i] *= -1;
    ll *suffix = getMinPrefixArray(inRow[row]);
    ll minCost = 10000000000000000LL;
    F0R(i, inRow[row].size() / 2 + 1) {
        ll cost = prefix[i] + suffix[inRow[row].size() / 2 - i];
        minCost = min(minCost, cost);
    }
    cout << baseCost << " " << minCost << endl;
    return baseCost + minCost;
}

int main() {
    ifstream fin("landscape.in");
    ofstream fout("landscape.out");
    fin >> n >> x >> y >> z;
    disForLong = (x + y) / z + 1;
    double lo = MAXPLOTS, hi = -MAXPLOTS, curr = 0;
    bool isChange = false;
    F0R(i, n) {
        int a, b;
        fin >> a >> b;
        diff[i] = b - a;
        curr += diff[i];
        double reff;
        if(diff[i] < 0) reff = curr + 0.5;
        if(diff[i] > 0) reff = curr - 0.5;
        if(diff[i] != 0) lo = min(lo, reff), hi = max(hi, reff), isChange = true;
    }
    if(!isChange) {
        fout << 0 << "\n";
        return 0;
    }
    hi -= lo - 1;
    curr = -lo;
    F0R(i, n) {
        F0R(j, abs(diff[i])) {
            if(diff[i] > 0) inRow[(int)(-0.5 + ++curr)].PB(i);
            else inRow[(int)(0.5 + --curr)].PB(i);
        }
    }
    ll cost = 0;
    F0R(i, hi) cost += getMinCost(i);
    fout << cost << "\n";
    return 0;
}
