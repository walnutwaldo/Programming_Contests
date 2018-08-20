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
#define MAXN 100000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n;
pair<ll, ll> cows[MAXN];

int main() {
    ifstream fin("pairup.in");
    ofstream fout("pairup.out");

    fin >> n;
    F0R(i, n) {
        ll time, num;
        fin >> num >> time;
        cows[i] = MP(time, num);
    }
    sort(cows, cows + n);
    int i = 0, j = n - 1;
    ll time = 0;
    while(i <= j) {
        ll r = min(cows[i].S, cows[j].S);
        cows[i].S -= r;
        cows[j].S -= r;
        time = max(time, cows[i].F + cows[j].F);
        if(cows[i].S <= 0) i++;
        if(cows[j].S <= 0) j--;
    }
    fout << time << endl;
    return 0;
}
