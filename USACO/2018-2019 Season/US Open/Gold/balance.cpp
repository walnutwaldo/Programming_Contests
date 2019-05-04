#include <bits/stdc++.h>

using namespace std;

#define MAXN 100000

int n, board[2][MAXN], cnt[2][2];
vector<int> loc[2][2];
long long numInv[2];

long long cntInversions(int* arr) {
	long long num1s = 0, res = 0;
	for (int i = 0; i < n; i++) {
		num1s += arr[i] == 1;
		res += (arr[i] == 0) * num1s;
	}
	return res;
}

int main() {
	ifstream cin("balance.in");
	ofstream cout("balance.out");
	cin >> n;
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < n; i++) {
			cin >> board[j][i];
			loc[j][board[j][i]].push_back(i);
			cnt[j][board[j][i]]++;
		}
		numInv[j] = cntInversions(board[j]);
	}
	long long res = abs(numInv[0] - numInv[1]);
	long long running = 0;
	for (int i = 0; i < min((int)loc[0][0].size(), (int)loc[1][1].size()); i++) {
		int lPos = loc[0][0][loc[0][0].size() - 1 - i];
		int rPos = loc[1][1][i];
		numInv[0] += n - 1 - lPos;
		numInv[1] += rPos;
		numInv[0] -= cnt[0][1];
		numInv[1] -= cnt[1][0];
		cnt[0][1]++;
		cnt[1][0]++;
		running += n + rPos - lPos;
		res = min(res, running + abs(numInv[0] - numInv[1]));
	}
	for (int j = 0; j < 2; j++) {
		cnt[j][0] = cnt[j][1] = 0;	
		for(int i = 0; i < n; i++) cnt[j][board[j][i]]++;
		numInv[j] = cntInversions(board[j]);
	}
	running = 0;
	for (int i = 0; i < min((int)loc[0][1].size(), (int)loc[1][0].size()); i++) {
		int lPos = loc[0][1][loc[0][1].size() - 1 - i];
		int rPos = loc[1][0][i];
		numInv[0] -= n - 1 - lPos;
		numInv[1] -= rPos;
		numInv[0] += cnt[0][1];
		numInv[1] += cnt[1][0];
		cnt[0][1]--;
		cnt[1][0]--;
		running += n + rPos - lPos;
		res = min(res, running + abs(numInv[0] - numInv[1]));
	}
	cout << res << endl;
	return 0;
}
