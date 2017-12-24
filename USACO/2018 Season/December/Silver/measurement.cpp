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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n;
ll g;
set<pair<ll, ll>> cows;
unordered_map<ll, ll> outputs;

int main() {
    ifstream fin("measurement.in");
    ofstream fout("measurement.out");
    fin >> n >> g;
    vector<tuple<int, ll, ll>> v;
    F0R(i, n) {
        int day;
        ll outputChange, id;
        fin >> day >> id >> outputChange;
        if(!outputs.count(id)) {
            outputs.insert(MP(id, g));
            cows.insert(MP(g, id));
        }
        v.PB(MT(day, id, outputChange));
    }
    sort(v.begin(), v.end());
    int res = 0;
    cows.insert(MP(g, 0));
    for(tuple<int, ll, ll> t : v) {
        ll currHighest = (*(--cows.end())).F;
        ll cowID = get<1>(t);
        ll outputChange = get<2>(t);
        bool isCurrHighest = (outputs[cowID] == currHighest);
        bool soloTop = (((*(----cows.end())).F) != currHighest);
        cows.erase(MP(outputs[cowID], cowID));
        outputs[cowID] += outputChange;
        cows.insert(MP(outputs[cowID], cowID));
        ll newHighest = (*(--cows.end())).F;
        bool currSoloTop = (((*(----cows.end())).F) != newHighest);
        if(isCurrHighest && (!soloTop || outputs[cowID] != newHighest || !currSoloTop) || !isCurrHighest && outputs[cowID] == newHighest) res++;
    }
    fout << res << "\n";
    return 0;
}
