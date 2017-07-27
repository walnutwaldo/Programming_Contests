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

int x, y;

int main() {
    ifstream fin("lostcow.in");
    ofstream fout("lostcow.out");

    fin >> x >> y;
    int mov = 1, goal = y - x;
    int total = 0;
    while(true) {
        if(abs(goal)/goal == abs(mov)/mov && abs(goal) <= abs(mov)) {
            total+=abs(goal);
            break;
        }
        total+=abs(2*mov);
        mov*=-2;
    }
    fout << total;
    return 0;
}
