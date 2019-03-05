#include <bits/stdc++.h>

#define F0R(i, a) for (int i = 0; i < a; i++)

#define PB push_back
#define LB lower_bound

using namespace std;

typedef vector<int> vi;

#define MAXN 100000

int n, a[MAXN];
vector<vi> cntr;
vi cntrtop;
int ptr;

bool possible(int pref) {
	vi v;
	F0R(i, pref) v.PB(a[i]);
	sort(v.rbegin(), v.rend());
	
	ptr = 0;
	cntr.clear();
	cntrtop.clear();
	F0R(i, pref) {
		int insidx = ptr;
		if(ptr < (int)cntrtop.size() && a[i] > cntrtop[ptr]) insidx = LB(cntrtop.begin() + ptr + 1, cntrtop.end(), a[i]) - cntrtop.begin();
		if(insidx == (int)cntrtop.size()) cntr.PB(vi()), cntrtop.PB(0);
		cntr[insidx].PB(a[i]);
		cntrtop[insidx] = a[i];
		while(!v.empty() && ptr < (int)cntr.size() && cntr[ptr].back() == v.back()) {
			v.pop_back();
			cntr[ptr].pop_back();
			if(cntr[ptr].empty()) ptr++;
			else cntrtop[ptr] = cntr[ptr].back();
		}
	}
	return v.empty();
}

int main() {
	ifstream cin("dishes.in");
	ofstream cout("dishes.out");
	cin >> n;
	F0R(i, n) cin >> a[i];
	int lo = 0, hi = n;
	while(lo < hi) {
		int mid = (lo + hi + 1) >> 1;
		if(possible(mid)) lo = mid;
		else hi = mid - 1;
	}
	cout << lo << endl;
	return 0;
}
