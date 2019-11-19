#include <bits/stdc++.h>

using namespace std;

int numcows, numdays;

long long st[1 << 17][2][2];

void upd(int idx) {
    if (!idx) { return; }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            st[idx][i][j] = max(st[2 * idx][i][0] + st[2 * idx + 1][1][j],
                                st[2 * idx][i][1] + st[2 * idx + 1][0][j]);
        }
    }
    upd(idx / 2);
}

int main() {
    ifstream cin("optmilk.in");
    ofstream cout("optmilk.out");
    cin >> numcows >> numdays;
    for (int i = 0; i < numcows; i++) {
        cin >> st[(1 << 16) + i][0][0];
        upd(((1 << 16) + i) / 2);
    }
    long long res = 0;
    for (int i = 0; i < numdays; i++) {
        int idx;
        cin >> idx;
        idx--;
        cin >> st[(1 << 16) + idx][0][0];
        upd(((1 << 16) + idx) / 2);
        res += st[1][0][0];
    }
    cout << res << endl;
    return 0;
}
