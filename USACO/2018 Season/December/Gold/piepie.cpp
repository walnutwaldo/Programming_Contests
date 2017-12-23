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
#define MAXN 100000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, minShares[2 * MAXN];
ll d, worth[2 * MAXN][2];
set<pair<ll, int>> gifts[2];

int main() {
    ifstream fin("piepie.in");
    ofstream fout("piepie.out");
    fin >> n >> d;
    F0R(i, 2 * n) minShares[i] = -1;
    queue<int> q;
    F0R(i, 2 * n) {
        fin >> worth[i][0] >> worth[i][1];
        if(worth[i][i < n] != 0) gifts[i < n].insert(MP(worth[i][i < n], i));
        else {
            minShares[i] = 1;
            q.push(i);
        }
    }
    while(!q.empty()) {
        int i = q.front();
        q.pop();
        vector<pair<ll, int>> toErase;
        auto hi = gifts[i >= n].LB(MP(worth[i][i >= n] + 1, -1));
        for(auto it = gifts[i >= n].LB(MP(worth[i][i >= n] - d, -1)); it != hi; ++it) {
            minShares[(*it).S] = minShares[i] + 1;
            q.push((*it).S);
            toErase.PB(*it);
        }
        for(const pair<ll, int> p : toErase) gifts[i >= n].erase(p);
    }
    F0R(i, n) fout << minShares[i] << "\n";
    return 0;
}
