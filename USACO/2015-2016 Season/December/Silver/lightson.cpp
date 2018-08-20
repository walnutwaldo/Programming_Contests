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
#define MAXN 100

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, m;
bool in[SQ(MAXN)], on[SQ(MAXN)];
vi connections[SQ(MAXN)];

int main() {
    ifstream fin("lightson.in");
    ofstream fout("lightson.out");
    fin >> n >> m;
    F0R(i, m) {
        int x, y, a, b;
        fin >> x >> y >> a >> b;
        connections[(x - 1) * n + (y - 1)].PB((a - 1) * n + (b - 1));
    }
    int numOn = 1;
    on[0] = true;
    in[0] = true;
    bool didSomething = true;
    for(const int j: connections[0]) {
        if(!on[j]) {
            on[j] = true;
            numOn++;
        }
    }
    while(didSomething) {
        didSomething = false;
        F0R(i, SQ(n)) {
            if(!in[i]) continue;
            if(i >= n && on[i - n] && !in[i - n]) {
                in[i - n] = true;
                didSomething = true;
                for(const int j: connections[i - n]) if(!on[j]) {
                        on[j] = true;
                        numOn++;
                    }
            }
            if(i < SQ(n) - n && on[i + n] && !in[i + n]) {
                in[i + n] = true;
                didSomething = true;
                for(const int j: connections[i + n]) if(!on[j]) {
                        on[j] = true;
                        numOn++;
                    }
            }
            if((i % n) > 0 && on[i - 1] && !in[i - 1]) {
                in[i - 1] = true;
                didSomething = true;
                for(const int j: connections[i - 1]) if(!on[j]) {
                        on[j] = true;
                        numOn++;
                    }
            }
            if((i % n) < n - 1 && on[i + 1] && !in[i + 1]) {
                in[i + 1] = true;
                didSomething = true;
                for(const int j: connections[i + 1]) if(!on[j]) {
                        on[j] = true;
                        numOn++;
                    }
            }
        }
    }
    fout << numOn << "\n";
    return 0;
}
