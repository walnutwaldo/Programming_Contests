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
#define MAXT 5000000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

bool possible[MAXT + 1], possibleWithWater[MAXT + 1];
int t, a, b, maximumFullness;

int main() {
    ifstream fin("feast.in");
    ofstream fout("feast.out");

    fin >> t >> a >> b;
    possible[0] = true;
    F0R(i, t + 1) {
        if(possible[i]) {
            possibleWithWater[i/2] = true;
            if(i + a <= t) possible[i + a] = true;
            if(i + b <= t) possible[i + b] = true;
            maximumFullness = max(maximumFullness, i);
        }
    }
    F0R(i, t + 1) {
        if(possibleWithWater[i]) {
            if(i + a <= t) possibleWithWater[i + a] = true;
            if(i + b <= t) possibleWithWater[i + b] = true;
            maximumFullness = max(maximumFullness, i);
        }
    }
    fout << maximumFullness << "\n";
    return 0;
}
