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
#define MAXX 100

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int x, y, k, m;
int dp[MAXX + 1][MAXX + 1];
queue<tuple<int, int, int>> q;

void tryAdding(int inX, int inY, int moves) {
    if(dp[inX][inY] != -1) return;
    dp[inX][inY] = moves;
    q.push(MT(inX, inY, moves));
}

int main() {
    ifstream fin("pails.in");
    ofstream fout("pails.out");
    fin >> x >> y >> k >> m;
    F0R(i, x + 1) F0R(j, y + 1) dp[i][j] = -1;
    dp[0][0] = 0;
    q.push(MT(0, 0, 0));
    int closest = INT_MAX;
    while(!q.empty()) {
        tuple<int, int, int> state = q.front();
        q.pop();
        int inX = get<0>(state);
        int inY = get<1>(state);
        int movesMade = get<2>(state);
        closest = min(closest, abs(m - inX - inY));
        if(movesMade < k) {
            tryAdding(0, inY, movesMade + 1);
            tryAdding(inX, 0, movesMade + 1);
            int pourToX = min(x - inX, inY);
            int pourToY = min(y - inY, inX);
            tryAdding(inX + pourToX, inY - pourToX, movesMade + 1);
            tryAdding(inX - pourToY, inY + pourToY, movesMade + 1);
            tryAdding(x, inY, movesMade + 1);
            tryAdding(inX, y, movesMade + 1);
        }
    }
    fout << closest << "\n";
    return 0;
}
