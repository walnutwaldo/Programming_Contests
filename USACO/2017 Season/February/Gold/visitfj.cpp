#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (a) - 1; i >= (b); i--)

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define MAXN 100

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, t;
ll dp[MAXN][MAXN][3], eatTime[MAXN][MAXN];

int main() {
    ifstream fin("visitfj.in");
    ofstream fout("visitfj.out");

    fin >> n >> t;
    F0R(y, n) F0R(x, n) fin >> eatTime[x][y];
    F0R(i, n) F0R(j, n) F0R(k, 3) dp[i][j][k] = -1;
    priority_queue<tuple<ll, int, int, int>, vector<tuple<ll, int, int, int>>, greater<tuple<ll, int, int, int>>> pq;
    pq.push(MT(0,0,0,0));
    while(!pq.empty()) {
        tuple<ll, int, int, int> state;
        int x, y, mod3;
        ll v;
        while(!pq.empty()) {
            state = pq.top();
            pq.pop();
            x = get<1>(state);
            y = get<2>(state);
            mod3 = get<3>(state);
            v = get<0>(state);
            if(dp[x][y][mod3] == -1)
                break;
        }
        dp[x][y][mod3] = v;
        if(x == n - 1 && y == n - 1) {
            fout << v << endl;
            return 0;
        }
        if(x < n - 1) pq.push(MT(v + t + ((mod3 == 2)?eatTime[x + 1][y]:0), x + 1, y, (mod3 + 1) % 3));
        if(y < n - 1) pq.push(MT(v + t + ((mod3 == 2)?eatTime[x][y + 1]:0), x, y + 1, (mod3 + 1) % 3));
        if(x > 0) pq.push(MT(v + t + ((mod3 == 2)?eatTime[x - 1][y]:0), x - 1, y, (mod3 + 1) % 3));
        if(y > 0) pq.push(MT(v + t + ((mod3 == 2)?eatTime[x][y - 1]:0), x, y - 1, (mod3 + 1) % 3));
    }
    return 0;
}
