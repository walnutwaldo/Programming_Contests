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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n, k;
int start[8][8], sum[10];
int piece[10][8][8];

bool canBeLeftShifted(int p) {
    if(sum[p] == 0) return false;
    F0R(r, n) if(piece[p][r][0] == 1) return false;
    return true;
}

bool canBeUpShifted(int p) {
    if(sum[p] == 0) return false;
    F0R(c, n) if(piece[p][0][c] == 1) return false;
    return true;
}

bool canBeRightShifted(int p) {
    if(sum[p] == 0) return false;
    F0R(r, n) if(piece[p][r][n - 1] == 1) return false;
    return true;
}

bool canBeDownShifted(int p) {
    if(sum[p] == 0) return false;
    F0R(c, n) if(piece[p][n - 1][c] == 1) return false;
    return true;
}

void leftShift(int p) {
    F0R(r, n) {
        F0R(c, n - 1) piece[p][r][c] = piece[p][r][c + 1];
        piece[p][r][n - 1] = 0;
    }
}

void upShift(int p) {
    F0R(c, n) {
        F0R(r, n - 1) piece[p][r][c] = piece[p][r + 1][c];
        piece[p][n - 1][c] = 0;
    }
}

void rightShift(int p) {
    F0R(r, n) {
        ROF(c, 1, n) piece[p][r][c] = piece[p][r][c - 1];
        piece[p][r][0] = 0;
    }
}

void downShift(int p) {
    F0R(c, n) {
        ROF(r, 1, n) piece[p][r][c] = piece[p][r - 1][c];
        piece[p][0][c] = 0;
    }
}

bool works(int p1, int p2) {
    bool ans = false;
    int rightShiftCount1 = 0;
    while(1) {
        int downShiftCount1 = 0;
        while(1) {
            int rightShiftCount2 = 0;
            while(1) {
                int downShiftCount2 = 0;
                while(1) {
                    bool work = true;
                    F0R(i, n) F0R(j, n) if(piece[p1][i][j] + piece[p2][i][j] != start[i][j]) {
                        work = false;
                    }
                    if(work) ans = true;
                    if(!ans && canBeDownShifted(p2)) {
                        downShift(p2);
                        downShiftCount2++;
                    } else {
                        F0R(i, downShiftCount2) upShift(p2);
                        break;
                    }
                }
                if(!ans && canBeRightShifted(p2)) {
                    rightShift(p2);
                    rightShiftCount2++;
                } else {
                    F0R(i, rightShiftCount2) leftShift(p2);
                    break;
                }
            }

            if(!ans && canBeDownShifted(p1)) {
                downShift(p1);
                downShiftCount1++;
            } else {
                F0R(i, downShiftCount1) upShift(p1);
                break;
            }
        }
        if(!ans && canBeRightShifted(p1)) {
            rightShift(p1);
            rightShiftCount1++;
        } else {
            F0R(i, rightShiftCount1) leftShift(p1);
            break;
        }
    }
    return ans;
}

int main() {
    ifstream fin("bcs.in");
    ofstream fout("bcs.out");
    fin >> n >> k;
    F0R(r, n) F0R(c, n) {
        char ch;
        fin >> ch;
        if(ch == '#') start[r][c] = 1;
    }
    F0R(i, k) {
        F0R(r, n) F0R(c, n) {
            char ch;
            fin >> ch;
            if(ch == '#') {
                piece[i][r][c] = 1;
                sum[i]++;
            }
        }
        while(canBeLeftShifted(i)) leftShift(i);
        while(canBeUpShifted(i)) upShift(i);
    }
    F0R(p1, k) FOR(p2, p1 + 1, k) if(works(p1, p2)) {
        fout << p1 + 1 << " " << p2 + 1 << "\n";
        return 0;
    }
    return 0;
}
