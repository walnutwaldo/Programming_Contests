#include<bits/stdc++.h>
#include "combo.h"

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define ran() (rand() & 0x7FFF)
#define rand31() ((ran() << 16) | (ran() << 1) | (ran() & 1))
#define rand32() ((ran() << 17) | (ran() << 2) | (ran() & 3))
#define rand63() (((ll)ran() << 48) | ((ll)ran() << 33) | ((ll)ran() << 18) | ((ll)ran() << 3) | ((ll)ran() & 7))
#define rand64() (((ll)ran() << 49) | ((ll)ran() << 34) | ((ll)ran() << 19) | ((ll)ran() << 4) | ((ll)ran() & 15))

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define X real()
#define Y imag()

#define PI acos(-1)

#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define SQ(x) ((x) * (x))

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef vector<ll> vll;
typedef vector<ull> vul;
typedef complex<ld> point;
typedef complex<ld> cld;
typedef vector<cld> vcld;

string res;
char letters[4]{'A', 'B', 'X', 'Y'};

string guess_sequence(int N) {
    int x = press("AB");
    if(x) {
        x = press("A");
        if(x) res = "A";
        else res = "B";
    } else {
        x = press("X");
        if(x) res = "X";
        else res = "Y";
    }
    if(N == 1) return res;
    vector<char> options;
    F0R(i, 4) if(res[0] != letters[i]) options.PB(letters[i]);
    FOR(i, 1, N - 1) {
        x = press(res + options[0] + res + options[1] + options[0] + res + options[1] + options[1] + res + options[1] + options[2]);
        if(x == sz(res)) res += options[2];
        else if(x == sz(res) + 1) res += options[0];
        else res += options[1];
    }
    x = press(res + "A" + res + "B");
    if(x > sz(res)) {
        x = press(res + "A");
        if(x > sz(res)) res += "A";
        else res += "B";
    } else {
        x = press(res + "X");
        if(x > sz(res)) res += "X";
        else res += "Y";
    }
    return res;
}
