//A
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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

char a, b;
int t;

int code(char c) {
    int code = 0;
    switch(c) {
    case 'v':
        code++;
    case '<':
        code++;
    case '^':
        code++;
    }
    return code;
}

char valOf(int i) {
    if(i == 0) return '>';
    if(i == 1) return '^';
    if(i == 2) return '<';
    if(i == 3) return 'v';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> a >> b >> t;
    t %= 4;
    int c1 = code(a);
    int c2 = code(b);
    int cw = valOf((c1 - t + 4) % 4);
    int ccw = valOf((c1 + t + 4) % 4);
    if(cw == b && ccw != b) cout << "cw\n";
    else if(ccw == b && cw != b) cout << "ccw\n";
    else cout << "undefined\n";
    return 0;
}
