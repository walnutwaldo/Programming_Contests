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
#define MAXN 200000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ll> point;

int n, start, numInCycle;
bool seen[MAXN], inCycle[MAXN];
vector<pair<int, ll>> tree[MAXN];
pii ig = MP(-1, -1);
vi cycle;
vector<ll> length, tailSize, prefixFar, suffixFar, prefixDiam, suffixDiam, prefixDiamHelper, suffixDiamHelper;

bool dfs(int node, int last) {
    seen[node] = true;
    for(const pair<int, ll> edge: tree[node]) {
        if(edge.F == last) continue;
        if(edge.F == start) {
            cycle.PB(node);
            inCycle[node] = true;
            length.PB(edge.S);
            numInCycle++;
            return true;
        }
        if(seen[edge.F]) continue;
        if(dfs(edge.F, node)) {
            cycle.PB(node);
            inCycle[node] = true;
            length.PB(edge.S);
            numInCycle++;
            return true;
        }
    }
    return false;
}

pair<ll, int> dfsFar(int node) {
    pair<ll, int> res = MP((ll)0, node);
    for(const pair<int, ll> edge : tree[node]) {
        if(!inCycle[edge.F] && MP(min(node, edge.F), max(node, edge.F)) != ig) {
            inCycle[edge.F] = true;
            pair<ll, int> temp = dfsFar(edge.F);
            temp.F += edge.S;
            res = max(res, temp);
            inCycle[edge.F] = false;
        }
    }
    return res;
}

ll calcDiam() {
    memset(inCycle, 0, sizeof(inCycle));
    inCycle[0] = true;
    int secondStart = dfsFar(0).S;
    inCycle[0] = false;
    inCycle[secondStart] = true;
    return dfsFar(secondStart).F;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    F0R(i, n) {
        int a, b;
        ll l;
        cin >> a >> b >> l;
        a--;
        b--;
        if(tree[a].size() > 0 && tree[b].size() > 0) start = a;
        tree[a].PB(MP(b, l));
        tree[b].PB(MP(a, l));
    }
    dfs(start, -1);
    reverse(cycle.begin(), cycle.end());
    reverse(length.begin(), length.end());
    F0R(i, numInCycle) tailSize.PB(dfsFar(cycle[i]).F);
    ll disInCycle = (ll)0;
    prefixFar.PB(tailSize[0]);
    prefixDiamHelper.PB(tailSize[0]);
    prefixDiam.PB((ll)0);
    FOR(i, 1, numInCycle) {
        disInCycle += length[i - 1];
        prefixFar.PB(max(prefixFar[i - 1], disInCycle + tailSize[i]));
        prefixDiamHelper.PB(max(prefixDiamHelper[i - 1], tailSize[i] - disInCycle));
        prefixDiam.PB(max(prefixDiam[i - 1], disInCycle + tailSize[i] + prefixDiamHelper[i - 1]));
    }
    disInCycle = (ll)0;
    suffixFar.PB(tailSize[numInCycle - 1]);
    suffixDiamHelper.PB(tailSize[numInCycle - 1]);
    suffixDiam.PB((ll)0);
    R0F(i, numInCycle - 1) {
        disInCycle += length[i];
        suffixFar.PB(max(suffixFar[numInCycle - i - 2], disInCycle + tailSize[i]));
        suffixDiamHelper.PB(max(suffixDiamHelper[numInCycle - i - 2], tailSize[i] - disInCycle));
        suffixDiam.PB(max(suffixDiam[numInCycle - i - 2], disInCycle + tailSize[i] + suffixDiamHelper[numInCycle - i - 2]));
    }
    ll minDiam = -1;
    int minRemove = -1;
    F0R(i, numInCycle) {
        ll currDiam;
        if(i < numInCycle - 1) currDiam = max(length[numInCycle - 1] + prefixFar[i] + suffixFar[numInCycle - i - 2],max(prefixDiam[i], suffixDiam[numInCycle - i - 2]));
        else currDiam = prefixDiam[i];
        if(minRemove == -1 || minDiam > currDiam) {
            minDiam = currDiam;
            minRemove = i;
        }
    }
    ig = MP(min(cycle[minRemove], cycle[(minRemove + 1) % numInCycle]), max(cycle[minRemove], cycle[(minRemove + 1) % numInCycle]));
    cout << calcDiam() << endl;
    return 0;
}
