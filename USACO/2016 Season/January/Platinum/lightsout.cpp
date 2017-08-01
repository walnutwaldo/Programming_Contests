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
#define FRONT 3
#define BACK 5
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
ll lengthOfWall[MAXN], hashAt[MAXN][MAXN], lengthOfSegment[MAXN][MAXN];
unordered_map<ll, vector<pii>> placesWithHash;
unordered_map<ll, ll> dp;
unordered_map<ll, int> direction;

ll disFromEnd(int i) {
    return min(lengthOfSegment[0][i], lengthOfSegment[i][n - i]);
}

ll act(int s, int l, int pos) {
    ll total = 0;
    while(s != 0 && (s + l) % n != 0) {
        int m = direction[hashAt[s][l] * PRIME + pos];
        if(pos == FRONT) {
            if(m == FRONT) total += lengthOfSegment[(s + n - 1) % n][1];
            else total += lengthOfSegment[s][l + 1];
        } else {
            if(m == FRONT) total += lengthOfSegment[(s + n - 1) % n][l + 1];
            else total += lengthOfSegment[s + l][1];
        }
        if(m == FRONT) s = (s + n - 1) % n;
        l++;
        pos = m;
    }
    return total;
}

ll solve(ll h, ll pos) {
    ll solutionHash = h * PRIME + pos;
    if(dp.count(solutionHash)) return dp[solutionHash];
    vector<pii> possible = placesWithHash[h];
    ll maxL = 0, maxR = 0;
    for(const pii loc : possible) {
        int s = loc.F;
        int l = loc.S;
        int e = (s + l) % n;
        if(s == 0 || e < s) continue;
        int nextS = (s + n - 1) % n;
        if(pos == FRONT) {
            maxL = max(maxL, lengthOfSegment[nextS][1] + solve(hashAt[nextS][l + 1], FRONT));
            maxR = max(maxR, lengthOfSegment[s][l + 1] + solve(hashAt[s][l + 1], BACK));
        } else {
            maxL = max(maxL, lengthOfSegment[nextS][l + 1] +solve(hashAt[nextS][l + 1], FRONT));
            maxR = max(maxR, lengthOfSegment[e][1] + solve(hashAt[s][l + 1], BACK));
        }
    }
    dp.insert(MP(solutionHash, min(maxL, maxR)));
    if(dp[solutionHash] == maxL) direction.insert(MP(solutionHash, FRONT));
    else direction.insert(MP(solutionHash, BACK));
    return dp[solutionHash];
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
    F0R(i, n) {
        solve(hashAt[i][0], FRONT);
        solve(hashAt[i][0], BACK);
    }
    ll l90 = 0, r90 = 0, l270 = 0, r270 = 0;
    FOR(i, 1, n) {
        ll l = act((i + n - 1) % n, 1, FRONT) + lengthOfSegment[(i + n - 1) % n][1] - disFromEnd(i);
        ll r = act(i, 1, BACK) + lengthOfSegment[i][1] - disFromEnd(i);
        if(dir[i] == DEG90) {
            l90 = max(l90, l);
            r90 = max(r90, r);
        } else {
            l270 = max(l270, l);
            r270 = max(r270, r);
        }
        cout << i << " " << l << " " << r << endl;
    }
    fout << max(min(l90, r90), min(l270, r270)) << "\n";
    return 0;
}
