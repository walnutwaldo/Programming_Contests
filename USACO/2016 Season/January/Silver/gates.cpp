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
#define UB upper_bound
#define LB lower_bound

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, changeX[4] {1, 0, -1, 0}, changeY[4] {0, 1, 0, -1};
set<pii> seen;
set<pair<pii, int>> seen2;

int getID(char c) {
    int id = 0;
    switch(c) {
    case 'S' :
        id++;
    case 'W' :
        id++;
    case 'N' :
        id++;
    }
    return id;
}

int main() {
    ifstream fin("gates.in");
    ofstream fout("gates.out");
    fin >> n;
    pii curPos = {0, 0};
    seen.insert(curPos);
    int numGates = 0;
    F0R(i, n) {
        char dir;
        fin >> dir;
        int dID = getID(dir);
        pii nextPos = {curPos.F + changeX[dID], curPos.S + changeY[dID]};
        pair<pii, int> edge = {curPos, dID};
        if(seen.count(nextPos) && !seen2.count(edge) && !seen2.count({nextPos, (dID + 2) % 4})) numGates++;
        seen.insert(nextPos);
        seen2.insert(edge);
        curPos = nextPos;
    }
    fout << numGates << "\n";
    return 0;
}
