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
typedef vector<pii> vpii;

int n;
vpii cows;

int main() {
    ifstream fin("cowqueue.in");
    ofstream fout("cowqueue.out");

    fin >> n;
    F0R(i, n) {
        int arrival, interigationTime;
        fin >> arrival >> interigationTime;
        cows.PB(MP(arrival, interigationTime));
    }
    sort(cows.begin(), cows.end());
    ll currTime = 0;
    F0R(i, n) {
        currTime = max(currTime, (ll)cows[i].F);
        currTime += cows[i].S;
    }
    fout << currTime;
    return 0;
}
