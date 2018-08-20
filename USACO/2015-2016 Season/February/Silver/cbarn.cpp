#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define MAXN 1000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, c[MAXN], in[MAXN];

void force(int place, int id) {
    if(in[place] == -1) {
        in[place] = id;
        return;
    }
    int other = in[place];
    if(((place + n - other) % n) >= ((place + n - id) % n)) {
        int temp = id;
        id = other;
        other = temp;
    }
    in[place] = id;
    force((place + 1) % n, other);
}

int main() {
    ifstream fin("cbarn.in");
    ofstream fout("cbarn.out");
    fin >> n;
    F0R(i, n) {
        fin >> c[i];
        in[i] = -1;
    }
    F0R(i, n) {
        F0R(j, c[i]) {
            force((i + j) % n, i);
        }
    }
    int cost = 0;
    F0R(i, n) {
        cost += SQ((i + n - in[i]) % n);
    }
    fout << cost << "\n";
    return 0;
}
