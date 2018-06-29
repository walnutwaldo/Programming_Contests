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

#ifdef WIN32
inline char getchar_unlocked() { return _getchar_nolock(); }
inline void putchar_unlocked(char c) { _putchar_nolock(c); }
#endif

#define MAXN 100000

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

template<class T> void print(T t) {
	string s = to_string(t);
	for(const char c : s) putchar_unlocked(c);
}

template<class T> void println(T t) {
	print(t);
	putchar_unlocked('\n');
}

ll nextLong() {
	ll res = 0;
	bool neg = 0;
	char c;
	while((c = getchar_unlocked()) != '-' && (c < '0' || c > '9')) {}
	if(c == '-') {
		neg = 1;
		c = getchar_unlocked();
	}
	while(c >= '0' && c <= '9') {
		res *= 10;
		res += (c - '0');
		c = getchar_unlocked();
	}
	if(neg) res *= -1;
	return res;
}

int nextInt() {
	int res = 0;
	bool neg = 0;
	char c;
	while((c = getchar_unlocked()) != '-' && (c < '0' || c > '9')) {}
	if(c == '-') {
		neg = 1;
		c = getchar_unlocked();
	}
	while(c >= '0' && c <= '9') {
		res *= 10;
		res += (c - '0');
		c = getchar_unlocked();
	}
	if(neg) res *= -1;
	return res;
}

struct State{

	ll base, strt;
	int numInt;

	State(ll bb = 0, ll ss = 0, int ni = 0) {
		base = bb;
		strt = ss;
		numInt = ni;
	}

	ll evalAt(ll x) { return base + SQ(x - strt); }

};

int n, k, loptr, hiptr;
ll m;
pair<ll, ll> loc[MAXN];
vector<pair<ll, ll>> locFinal;
State states[MAXN];

ll timeBetter(State s1, State s2) { return max(s2.strt, 1 + (s1.base - s2.base - SQ(s2.strt) + SQ(s1.strt)) / (2 * s1.strt - 2 * s2.strt)); }

void addState(State s) {
	while(hiptr - loptr > 1) {
		ll t1 = timeBetter(states[hiptr - 2], states[hiptr - 1]);
		ll t2 = timeBetter(states[hiptr - 2], s);
		if(t2 < t1 || (t1 == t2 && states[hiptr - 1].evalAt(t1) > s.evalAt(t1))) hiptr--;
		else break;
	}
	states[hiptr++] = s;
}

pair<ll, int> getBest(ll strt, ll C) {
	while(hiptr - loptr > 1 && states[loptr].evalAt(strt) > states[loptr + 1].evalAt(strt)) loptr++;
	return MP(states[loptr].evalAt(strt) + C, states[loptr].numInt + 1);
}

pair<ll, int> solveDP(ll C) {
	loptr = hiptr = 0;
	addState(State(0, locFinal[0].F, 0));
	F0R(i, n) {
		pair<ll, int> best = getBest(locFinal[i].S, C);
		if(i == n - 1) return best;
		ll base = best.F - SQ(max(0LL, locFinal[i].S - locFinal[i + 1].F));
		ll strt = locFinal[i + 1].F;
		addState(State(base, strt, best.S));
	}
}

ll solve() {
	ll lo = 0, hi = m * m;
	while(lo < hi) {
		ll mid = (lo + hi) >> 1;
		if(solveDP(mid).S <= k) hi = mid;
		else lo = mid + 1;
	}
	pair<ll, int> p = solveDP(lo);
	return p.F - lo * k;
}

int main() {
	n = nextInt();
	m = nextLong();
	k = nextInt();
	F0R(i, n) {
		loc[i].F = nextLong();
		loc[i].S = nextLong();
		if(loc[i].F > loc[i].S) swap(loc[i].F, loc[i].S);
		loc[i].S++;
		loc[i].S *= -1;
	}
	sort(loc, loc + n);
	F0R(i, n) loc[i].S *= -1;
	F0R(i, n) if(locFinal.empty() || loc[i].S > locFinal.back().S) locFinal.PB(loc[i]);
	n = sz(locFinal);
	k = min(k, n);
	println(solve());
}
