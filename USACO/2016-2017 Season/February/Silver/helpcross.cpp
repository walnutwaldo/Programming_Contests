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
#define UB upper_bound
#define MAXN 20000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int N, C;
pii cows[MAXN], chickens[MAXN];
bool used[MAXN];

int main() {
    ifstream fin("helpcross.in");
    ofstream fout("helpcross.out");

    fin >> C >> N;
    F0R(i, C) {
        int T;
        fin >> T;
        chickens[i] = MP(T, i);
    }
    F0R(i, N) {
        int S,E;
        fin >> S >> E;
        cows[i] = MP(E, S);
    }
    sort(chickens, chickens + C);
    sort(cows, cows + N);

    int res = 0;
    F0R(i, N) {
        int k = UB(chickens, chickens + C, MP(cows[i].S, -1)) - chickens;
        while(k < C && chickens[k].F <= cows[i].F) {
            if(!used[chickens[k].S]) {
                used[chickens[k].S] = true;
                res++;
                break;
            }
            k++;
        }
    }
    fout << res << endl;
    return 0;
}
