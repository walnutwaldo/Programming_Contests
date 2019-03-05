#include <bits/stdc++.h>

#define F0R(i, a) for (int i = 0; i < a; i++)

#define PB push_back

using namespace std;

typedef vector<int> vi;

#define MAXN 100000

int n, mx, base[MAXN + 1];
vi cntr[MAXN + 1];

int main() {
	ifstream cin("dishes.in");
	ofstream cout("dishes.out");
	cin >> n;
	int mx = 0;
	F0R(i, n) {
		int a;
		cin >> a;
		if(a < mx) {
			cout << i << endl;
			exit(0);
		}
		for(int j = a; j && !base[j]; j--) base[j] = a;
		while(!cntr[base[a]].empty() && cntr[base[a]].back() < a) {
			mx = max(mx, cntr[base[a]].back());
			cntr[base[a]].pop_back();
		}
		cntr[base[a]].PB(a);
	}
	cout << n << endl;
	return 0;
}
