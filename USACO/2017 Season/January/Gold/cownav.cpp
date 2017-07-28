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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int N;
int changeX[4] {1,0,-1,0}, changeY[4] {0,1,0,-1};
bool added[20][20][20][20][4], open[20][20];
queue<tuple<int,int,int,int,int,int>> q;

bool legal(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && open[x][y]);
}

void insertIntoQueue(int moves, int x1, int y1, int x2, int y2, int direction) {
    q.push(make_tuple(moves, x1, y1, x2, y2, direction));
    added[x1][y1][x2][y2][direction] = true;
}

pii nextPos(int x, int y, int direction) {
    if(x == N-1 && y == N-1)
        return MP(x,y);
    int nextX = x + changeX[direction];
    int nextY = y + changeY[direction];
    if(legal(nextX, nextY))
        return MP(nextX, nextY);
    else
        return MP(x, y);
}

int main() {
    ifstream fin("cownav.in");
    ofstream fout("cownav.out");

    fin >> N;
    R0F(y, N) {
        F0R(x, N) {
            char c;
            fin >> c;
            open[x][y] = (c == 'E');
        }
    }
    added[0][0][0][0][0] = true;
    q.push(make_tuple(0,0,0,0,0,0));
    while(!q.empty()) {
        tuple<int,int,int,int,int,int> curr = q.front();
        q.pop();
        int moves = get<0>(curr);
        int x1 = get<1>(curr);
        int y1 = get<2>(curr);
        int x2 = get<3>(curr);
        int y2 = get<4>(curr);
        int direction = get<5>(curr);
        if(x1 == N-1 && y1 == N-1 && x2 == N-1 && y2 == N-1) {
            fout << moves;
            return 0;
        }
        if(!added[x1][y1][x2][y2][(direction + 1) % 4]) insertIntoQueue(moves+1,x1,y1,x2,y2,(direction + 1) % 4);
        if(!added[x1][y1][x2][y2][(direction + 3) % 4]) insertIntoQueue(moves+1,x1,y1,x2,y2,(direction + 3) % 4);
        pii nextPos1 = nextPos(x1, y1, direction);
        pii nextPos2 = nextPos(x2, y2, (direction + 1) % 4);
        if(!added[nextPos1.F][nextPos1.S][nextPos2.F][nextPos2.S][direction]) insertIntoQueue(moves+1, nextPos1.F, nextPos1.S, nextPos2.F, nextPos2.S, direction);
    }
    return 0;
}
