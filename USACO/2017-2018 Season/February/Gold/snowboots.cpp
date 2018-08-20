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
#define MAXB 100000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n, b;
map<ll, int, greater<ll>> lengths;
vector<pair<ll, int>> tiles;
vector<pair<pair<ll, int>, int>> boots;
set<int> on;
bool possible[MAXB];

int main() {
    ifstream fin("snowboots.in");
    ofstream fout("snowboots.out");
    fin >> n >> b;
    F0R(i, n) {
        ll f;
        fin >> f;
        if(i != 0 && i != n - 1)
            tiles.PB(MP(f, i));
    }
    F0R(i, b) {
        ll s;
        int d;
        fin >> s >> d;
        boots.PB(MP(MP(s, d), i));
    }
    sort(tiles.begin(), tiles.end());
    sort(boots.begin(), boots.end());
    int currBoot = 0;
    on.insert(0), on.insert(n - 1);
    lengths[n - 1] = 1;
    for(const pair<ll, int> p : tiles) {
        ll longest = (*lengths.begin()).F;
        while(currBoot < b && boots[currBoot].F.F < p.F)
            if(boots[currBoot++].F.S >= longest)
                possible[boots[currBoot - 1].S] = 1;
        auto pos = on.UB(p.S);
        int upperVal = *pos;
        int lowerVal = *(--pos);
        on.insert(p.S);
        lengths[upperVal - p.S]++, lengths[p.S - lowerVal]++;
        if(--lengths[upperVal - lowerVal] == 0)
            lengths.erase(upperVal - lowerVal);
    }
    ll longest = (*lengths.begin()).F;
    while(currBoot < b)
        possible[boots[currBoot++].S] = 1;
    F0R(i, b) fout << possible[i] << "\n";
    return 0;
}
