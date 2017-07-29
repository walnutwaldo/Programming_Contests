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

int n;
int changeX[4] {1, 0, -1, 0}, changeY[4] {0, 1, 0, -1};
map<pii, int> lastTime;

int idOf(char c) {
    int id = 0;
    switch(c) {
    case 'S':
        id++;
    case 'W':
        id++;
    case 'N':
        id++;
    }
    return id;
}

int main() {
    ifstream fin("mowing.in");
    ofstream fout("mowing.out");
    fin >> n;
    pii curPos = MP(0, 0);
    int time = 0;
    lastTime.insert(MP(curPos, time));
    int timeNeeded = -1;
    F0R(i, n) {
        char dir;
        int steps;
        fin >> dir >> steps;
        int dID = idOf(dir);
        F0R(j, steps) {
            time++;
            curPos.F += changeX[dID];
            curPos.S += changeY[dID];
            if(lastTime.count(curPos) && (timeNeeded > time - lastTime[curPos] || timeNeeded == -1))
                timeNeeded = time - lastTime[curPos];
            if(!lastTime.count(curPos)) lastTime.insert(MP(curPos, time));
            lastTime[curPos] = time;
        }
    }
    fout << timeNeeded << endl;
    return 0;
}
