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
#define MAXN 50000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, numWin;
bool inE[MAXN * 2];
vi firstHalf, secondHalf;

int main() {
    ifstream fin("cardgame.in");
    ofstream fout("cardgame.out");
    fin >> n;
    F0R(i, n / 2) {
        int cardNum;
        fin >> cardNum;
        inE[--cardNum] = true;
        firstHalf.PB(cardNum);
    }
    F0R(i, n / 2) {
        int cardNum;
        fin >> cardNum;
        inE[--cardNum] = true;
        secondHalf.PB(cardNum);
    }
    int candidateCard = -1;
    F0R(i, n / 2) {
        while(inE[++candidateCard]){}
        secondHalf.PB(candidateCard);
    }
    F0R(i, n / 2) {
        while(inE[++candidateCard]){}
        firstHalf.PB(candidateCard);
    }
    sort(firstHalf.begin(), firstHalf.end());
    sort(secondHalf.rbegin(), secondHalf.rend());
    int undef = 0;
    F0R(i, n) {
        if(inE[firstHalf[i]]) undef++;
        else if(undef > 0) {
            numWin++;
            undef--;
        }
    }
    undef = 0;
    F0R(i, n) {
        if(inE[secondHalf[i]]) undef++;
        else if(undef > 0) {
            numWin++;
            undef--;
        }
    }
    fout << numWin << "\n";
    return 0;
}
