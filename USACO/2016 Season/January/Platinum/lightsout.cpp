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
#define MAXN 200
#define PRIME 79
#define DEG90 31
#define DEG270 53

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n;
pii corners[MAXN];
ll dir[MAXN];
ll lengthOfWall[MAXN], hashAt[MAXN][MAXN], lengthOfSegment[MAXN][MAXN], dp[MAXN][MAXN][MAXN][2];
bool solved[MAXN][MAXN][MAXN][2];
unordered_map<ll, vector<pii>> placesWithHash;
unordered_map<ll, int> direction;

ll disFromEnd(int i) {
    return min(lengthOfSegment[0][i], lengthOfSegment[i][n - i]);
}

ll solve(int cs, int cl, int sPos, int pos) {
    if(cs == 0 || (cs + cl) % n < cs) return -disFromEnd((cs + sPos) % n);
    if(solved[cs][cl][sPos][pos]) return dp[cs][cl][sPos][pos];
    ll h = hashAt[cs][cl];
    ll h2 = h * PRIME + pos;
    ll lMax = -1000000, rMax = -1000000;
    if(direction.count(h2)) {
        if(direction[h2] == 0) rMax = 0;
        else lMax = 0;
    } else {
        vector<pii> possbilePositions = placesWithHash[h];
        for(const pii p : possbilePositions) {
            int s = p.F;
            int l = p.S;
            if(s == 0 || (s + l) % n < s) {
                continue;
            }
            if(pos == 0) {
                lMax = max(lMax, lengthOfSegment[(s + n - 1) % n][1] + solve((s + n - 1) % n, l + 1, sPos + 1, 0));
                rMax = max(rMax, lengthOfSegment[s][l + 1] + solve(s, l + 1, sPos, 1));
            } else {
                lMax = max(lMax, lengthOfSegment[(s + n - 1) % n][l + 1] + solve((s + n - 1) % n, l + 1, sPos + 1, 0));
                rMax = max(rMax, lengthOfSegment[(s + l) % n][1] + solve(s, l + 1, sPos, 1));
            }
        }
    }
    if(lMax < rMax) {
        if(pos == 0) {
            dp[cs][cl][sPos][pos] = lengthOfSegment[(cs + n - 1) % n][1] + solve((cs + n - 1) % n, cl + 1, sPos + 1, 0);
        } else {
            dp[cs][cl][sPos][pos] = lengthOfSegment[(cs + n - 1) % n][cl + 1] + solve((cs + n - 1) % n, cl + 1, sPos + 1, 0);
        }
        direction[h2] = 0;
    } else {
        if(pos == 0) {
            dp[cs][cl][sPos][pos] = lengthOfSegment[cs][cl + 1] + solve(cs, cl + 1, sPos, 1);
        } else {
            dp[cs][cl][sPos][pos] = lengthOfSegment[(cs + cl) % n][1] + solve(cs, cl + 1, sPos, 1);
        }
        direction[h2] = 1;
    }
    solved[cs][cl][sPos][pos] = true;
    return dp[cs][cl][sPos][pos];
}

int main() {
    ifstream fin("lightsout.in");
    ofstream fout("lightsout.out");
    fin >> n;
    F0R(i, n) {
        int x, y;
        fin >> x >> y;
        corners[i] = MP(x, y);
    }
    F0R(i, n) {
        pii curr = corners[i], after = corners[(i + 1) % n];
        lengthOfWall[i] = abs(curr.F - after.F + curr.S - after.S);
    }
    F0R(i, n) {
        pii before = corners[(i + n - 1) % n], curr = corners[i], after = corners[(i + 1) % n];
        int x1 = curr.F - before.F;
        int y1 = curr.S - before.S;
        int x2 = after.F - curr.F;
        int y2 = after.S - curr.S;
        int cross = x1 * y2 - x2 * y1;
        if(cross > 0) dir[i] = DEG270;
        else dir[i] = DEG90;
    }
    F0R(s, n) {
        ll h = dir[s];
        ll d = 0;
        F0R(l, n) {
            if(!placesWithHash.count(h)) {
                vector<pii> v;
                placesWithHash.insert(MP(h, v));
            }
            placesWithHash[h].PB(MP(s, l));
            hashAt[s][l] = h;
            lengthOfSegment[s][l] = d;
            h *= PRIME;
            h += lengthOfWall[(s + l) % n];
            h *= PRIME;
            h += dir[(s + l + 1) % n];
            d += lengthOfWall[(s + l) % n];
        }
    }
    ll maxTravel = 0;
    F0R(i, n) {
        maxTravel = max(maxTravel, solve(i, 0, 0, 0));
    }
    fout << maxTravel << "\n";
    return 0;
}
