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
#define MAXN 100

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<ull> vul;
typedef complex<ld> point;

int n, m, k, order[MAXN];
vi hierarchy;
bool decided[MAXN], isSet[MAXN];

bool fillable() {
	int currS = 0;
	F0R(currH, hierarchy.size()) {
		if(decided[hierarchy[currH]]) {
			while(currS < n && (!isSet[currS] || order[currS] != hierarchy[currH])) currS++;
			if(currS == n) return 0;
		} else {
			while(currS < n && isSet[currS]) currS++;
			if(currS == n) return 0;
		}
		currS++;
	}
	return 1;
}

bool possible(int spot) {
	order[spot] = 0;
	decided[0] = 1;
	isSet[spot] = 1;
	bool res = fillable();
	isSet[spot] = 0;
	decided[0] = 0;
	return res;
}

int main() {
	ifstream fin("milkorder.in");
	ofstream fout("milkorder.out");
	fin >> n >> m >> k;
	F0R(i, m) {
		int cow;
		fin >> cow;
		hierarchy.PB(cow - 1);
	}
	F0R(i, k) {
		int cow, spot;
		fin >> cow >> spot;
		decided[cow - 1] = 1;
		order[spot - 1] = cow - 1;
		isSet[spot - 1] = 1;
	}
	if(decided[0]) {
		int spot = 0;
		F0R(i, n) if(isSet[i] && order[i] == 0) spot = i;
		fout << spot + 1 << endl;
		return 0;
	} else F0R(i, n) if(!isSet[i] && possible(i)) {
		fout << i + 1 << endl;
		return 0;
	}
}
