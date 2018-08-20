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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, m;
vector<pii> road, bessie;

int main() {
    ifstream fin("speeding.in");
    ofstream fout("speeding.out");

    fin >> n >> m;
    F0R(i, n) {
        int l, s;
        fin >> l >> s;
        road.PB(MP(s, l));
    }
    F0R(i, m) {
        int l, s;
        fin >> l >> s;
        bessie.PB(MP(s, l));
    }
    int maxOver = 0;
    int i = 0, j = 0;
    while(i < n && j < m) {
        maxOver = max(maxOver, bessie[j].F - road[i].F);
        int travel = min(bessie[j].S, road[i].S);
        bessie[j].S -= travel;
        road[i].S -= travel;
        if(bessie[j].S == 0) j++;
        if(road[i].S == 0) i++;
    }
    fout << maxOver << "\n";
    return 0;
}
