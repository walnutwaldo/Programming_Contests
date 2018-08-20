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
bool tipped[10][10];

int main() {
    ifstream fin("cowtip.in");
    ofstream fout("cowtip.out");

    fin >> N;
    F0R(y, N) {
        string s;
        fin >> s;
        F0R(x,N) {
            tipped[x][y] = s[x] == '1';
        }
    }
    int count = 0;
    while(true) {
        int lastX = -1;
        int lastY = -1;
        F0R(y, N) F0R(x,N) if(tipped[x][y]) {
            lastX = x;
            lastY = y;
        }
        if(lastX == -1)
            break;
        F0R(x, lastX + 1) F0R(y, lastY + 1) tipped[x][y] = !tipped[x][y];
        count++;
    }
    fout << count;
    return 0;
}
