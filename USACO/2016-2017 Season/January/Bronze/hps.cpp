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

int N , diff, win;

int main() {
    ifstream fin("hps.in");
    ofstream fout("hps.out");

    fin >> N;
    F0R(i, N){
        int first, second;
        fin >> first >> second;
        if(first != second) diff++;
        if(second == (first) % 3 + 1) win++;
    }
    fout << max(win, diff - win);

    return 0;
}
