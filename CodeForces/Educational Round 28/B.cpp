#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define X real()
#define Y imag()
#define MAXN 45

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n, k, numOn[MAXN];
ll m, t[MAXN], totalT;

int maxScore(ll timeLeft, int tasksLeft) {
    int left[k];
    F0R(i, k) left[i] = tasksLeft;
    ll currTime = 0;
    int curr = 0;
    int p = 0;
    while(1) {
        while(curr < k && left[curr] == 0) curr++;
        if(curr == k) break;
        if(t[curr] + currTime > timeLeft) break;
        currTime += t[curr];
        p++;
        left[curr]--;
    }
    return p;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k >> m;
    F0R(i, k) {
        cin >> t[i];
        totalT += t[i];
    }
    sort(t, t + k);
    int res = 0;
    F0R(numFull, 1 + min(n, (int)(m / totalT))) {
        res = max(res, numFull * (k + 1) + maxScore(m - numFull * totalT, n - numFull));
    }
    cout << res << "\n";
    return 0;
}
