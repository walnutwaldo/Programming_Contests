#include <bits/stdc++.h>

using namespace std;

#define MOD 2019201997LL

#define MAXN 7500

int n, k;
long long mst[MAXN];

long long cost(int x, int y) { return MOD - 84 * min(x, y) - 48 * max(x, y); }

void constMST() {
	bool vis[n];
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i < n; i++) mst[i] = 1e15;
	mst[0] = 0;
	while (true) {
		int closest = -1;
		for (int i = 0; i < n; i++) if(!vis[i] && (closest == -1 || mst[i] < mst[closest])) closest = i;
		if (closest == -1) break;
		vis[closest] = 1;
		for (int next = 0; next < n; next++) if (!vis[next]) mst[next] = min(mst[next], cost(closest + 1, next + 1));
	}
}

int main() {
	ifstream cin("walk.in");
	ofstream cout("walk.out");
	cin >> n >> k;
	constMST();
	sort(mst + 1, mst + n);
	cout << mst[n + 1 - k] << endl;
}
