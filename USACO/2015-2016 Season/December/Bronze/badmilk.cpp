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
#define MAXN 50
#define MAXM 50

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, m, d, s, numDrank[MAXM];
bool drank[MAXM][MAXN];
bool possible[MAXM];

int main() {
    ifstream fin("badmilk.in");
    ofstream fout("badmilk.out");

    fin >> n >> m >> d >> s;
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> timeStamps;
    priority_queue<pii, vector<pii>, greater<pii>> sick;
    F0R(i, d) {
        int p, m, t;
        fin >> p >> m >> t;
        p--;
        m--;
        t--;
        timeStamps.push(MT(t, p, m));
    }
    F0R(i, s) {
        int p, t;
        fin >> p >> t;
        p--;
        t--;
        sick.push(MP(t, p));
    }
    F0R(i, m) possible[i] = true;
    int currTime = 0;
    while(currTime <= 100) {
        if(!sick.empty() && sick.top().F == currTime) {
            int person = sick.top().S;
            sick.pop();
            F0R(i, m) possible[i] = possible[i] && drank[i][person];
        } else if(!timeStamps.empty() && get<0>(timeStamps.top()) == currTime) {
            int person = get<1>(timeStamps.top());
            int milk = get<2>(timeStamps.top());
            timeStamps.pop();
            if(!drank[milk][person]) numDrank[milk]++;
            drank[milk][person] = true;
        } else currTime++;
    }
    int minNeeded = 0;
    F0R(i, m) if(possible[i]) minNeeded = max(minNeeded, numDrank[i]);
    fout << minNeeded << "\n";
    return 0;
}
