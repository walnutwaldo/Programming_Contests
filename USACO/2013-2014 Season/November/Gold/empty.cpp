#include <bits/stdc++.h>

using namespace std;

int n, k;
int cnt[3000000];

int main() {
    ifstream cin("empty.in");
    ofstream cout("empty.out");
    cin >> n >> k;
    int cowcnt = 0;
    for (int i = 0; i < k; i++) {
        int x, y;
        long long a, b;
        cin >> x >> y >> a >> b;
        for (int j = 1; j <= y; j++) {
            cnt[(a * j + b) % n] += x;
        }
    }
    int running = 0;
    for (int i = 0; i < 2 * n; i++) {
        running += cnt[i % n];
        cnt[i % n] = 0;
        if (running > 0) {
            cnt[i % n]++;
            running--;
        }
    }
    for (int i = 0; i < n; i++) {
        if (cnt[i] == 0) {
            cout << i << endl;
            exit(0);
        }
    }
    return 0;
}
