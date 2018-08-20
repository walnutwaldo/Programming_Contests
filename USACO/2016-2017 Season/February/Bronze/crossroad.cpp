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

int N, currSide[11];

int main() {
    ifstream fin("crossroad.in");
    ofstream fout("crossroad.out");

    fin >> N;
    FOR(i, 1, 11) currSide[i] = -1;
    int crossings = 0;
    F0R(i, N) {
        int id, side;
        fin >> id >> side;
        if(currSide[id] != -1 && currSide[id] != side)
            crossings++;
        currSide[id] = side;
    }
    fout << crossings;
    return 0;
}
