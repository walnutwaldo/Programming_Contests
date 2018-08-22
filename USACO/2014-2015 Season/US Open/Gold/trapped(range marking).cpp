#include <bits/stdc++.h>

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

#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define SQ(x) ((x) * (x))

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef vector<ll> vll;
typedef vector<ull> vul;
typedef complex<ld> point;
typedef complex<ld> cld;
typedef vector<cld> vcld;

#define MAXN 100000

int n, a[MAXN];
vector<tuple<int, int, int>> v;

int main() {
	ifstream fin("trapped.in");
	ofstream fout("trapped.out");
    fin >> n;
    F0R(i, n) {
        int s, p;
        fin >> s >> p;
        v.PB(MT(p, s, 0));
    }
    sort(all(v));
    F0R(i, n) v[i] = MT(get<1>(v[i]), get<0>(v[i]), i);
    sort(v.rbegin(), v.rend());
    F0R(i, n) v[i] = MT(get<1>(v[i]), get<0>(v[i]), get<2>(v[i]));
    set<tuple<int, int, int>> s;
    F0R(i, n) {
        if(s.empty()) {
            s.insert(v[i]);
            continue;
        }
        auto ptr = s.UB(v[i]);
        if(ptr != s.end() && get<0>(*ptr) - get<0>(v[i]) <= min(get<1>(*ptr), get<1>(v[i]))) {
            a[get<2>(v[i])]++;
            a[get<2>(*ptr)]--;
        }
        if(ptr-- != s.begin() && get<0>(v[i]) - get<0>(*ptr) <= min(get<1>(*ptr), get<1>(v[i]))) {
            a[get<2>(*ptr)]++;
            a[get<2>(v[i])]--;
        }
        s.insert(v[i]);
    }
    sort(all(v));
    int ans = 0, running = 0;
    F0R(i, n - 1) {
        running += a[i];
        if(running) ans += get<0>(v[i + 1]) - get<0>(v[i]);
    }
    fout << ans << endl;
}
