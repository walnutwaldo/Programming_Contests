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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n;
pii corners[MAXN];
int dir[MAXN];
ll lengthOfWall[MAXN], disToExit[MAXN];
unordered_map<ll, ll> occurences;

ll getHash(int s, int e) {
    if(s == e) return dir[s];
    int curr = (s + 1) % n;
    ll h = dir[s];
    while(true) {
        h *= PRIME;
        h += lengthOfWall[(curr + n - 1) % n];
        h *= PRIME;
        h += dir[curr];
        if(curr == e) break;
        curr = (curr + 1) % n;
    }
    return h;
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
        int dot = x1 * y2 - x2 * y1;
        if(dot > 0) dir[i] = 31;
        else dir[i] = 53;
    }
    disToExit[0] = 0;
    FOR(i, 1, n) {
        disToExit[i] = disToExit[i - 1] + lengthOfWall[i - 1];
    }
    ROF(i, 1, n) {
        disToExit[i] = min(disToExit[i], disToExit[(i + 1) % n] + lengthOfWall[i]);
    }
    F0R(s, n) {
        F0R(l, n) {
            ll h = getHash(s, (s + l) % n);
            if(!occurences.count(h)) occurences.insert(MP(h, 0));
            occurences[h]++;
        }
    }
    ll maxNeeded = 0;
    F0R(s, n) {
        if(s == 0) continue;
        ll traveled = 0;
        int curr = (s + 1) % n;
        ll h = dir[s];
        while(true) {
            if(occurences[h] == 1) {
                cout << s << " h " << traveled + disToExit[(curr + n - 1) % n] - disToExit[s] << endl;
                maxNeeded = max(maxNeeded, traveled + disToExit[(curr + n - 1) % n] - disToExit[s]);
                break;
            }
            h *= PRIME;
            h += lengthOfWall[(curr + n - 1) % n];
            h *= PRIME;
            h += dir[curr];
            traveled += lengthOfWall[(curr + n - 1) % n];
            if(curr == 0) {
                cout << s << " c " << traveled - disToExit[s] << endl;
                maxNeeded = max(maxNeeded, traveled - disToExit[s]);
                break;
            }
            curr = (curr + 1) % n;
        }
    }
    fout << maxNeeded << "\n";
    return 0;
}
