#include <bits/stdc++.h>

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

struct bigint{

    const static int BASE = 10, DIGITS = 200;
    int digits[DIGITS];

    bigint(const bigint& b) { F0R(i, DIGITS) digits[i] = b.digits[i]; }

    bigint(const string& s) {
        F0R(i, DIGITS) if(i >= sz(s)) digits[i] = 0;
        else digits[i] = s[sz(s) - 1 - i] - '0';
    }

    bigint(int val) {
        F0R(i, DIGITS) digits[i] = 0;
        *this += val;
    }

    void fix() {
        F0R(i, DIGITS - 1) {
            digits[i + 1] += digits[i] / BASE;
            digits[i] %= BASE;
            if(digits[i] < 0) {
                digits[i] += BASE;
                digits[i + 1]--;
            }
        }
    }

    bigint operator+(int x) {
        bigint res(*this);
        res += x;
        return res;
    }

    bigint operator-(int x) {
        bigint res(*this);
        res += -x;
        return res;
    }

    bigint operator+(bigint b) {
        bigint res(*this);
        F0R(i, DIGITS) res[i] += b[i];
        res.fix();
        return res;
    }

    void operator+=(bigint b){
        F0R(i, DIGITS) digits[i] += b[i];
        fix();
    }

    void operator+=(int x) {
        digits[0] += x;
        fix();
    }

    void div2() {
        ROF(i, 1, DIGITS) if(digits[i] & 1) {
            digits[i] ^= 1;
            digits[i - 1] += BASE;
        }
        F0R(i, DIGITS) digits[i] >>= 1;
    }

    void operator *=(int x) {
        F0R(i, DIGITS) digits[i] *= x;
        fix();
    }

    void operator =(bigint b) { F0R(i, DIGITS) digits[i] = b[i]; }

    int& operator[](int i) { return digits[i]; }

    string tostring() {
        string res;
        R0F(i, DIGITS) if(res != "" || digits[i]) res += '0' + digits[i];
        if(res == "") return "0";
        return res;
    }

    bool operator <(bigint b) {
        R0F(i, DIGITS) {
            if(digits[i] < b[i]) return 1;
            if(digits[i] > b[i]) return 0;
         }
         return 0;
    }

    bool iszero() {
        F0R(i, DIGITS) if(digits[i]) return 0;
        return 1;
    }

};

int baseDepth = 0;

bigint solve(bigint node, bigint mn) {
    if(node.iszero()) return bigint(0);
    string l, r;
    cout << node.tostring() << endl;
    cin >> l >> r;
    if(mn[0] % 2 == 1) {
        bigint half = mn; half.div2();
        return half + solve(bigint(l), half) + 1;
    } else {
        bigint half = mn;
        half.div2();
        return half + solve(bigint(r), half - 1) + 1;
    }
}

bigint solveR(bigint node) {
    if(node.iszero()) return bigint(0);
    string l, r;
    cout << node.tostring() << endl;
    cin >> l >> r;
    bigint onRight = solveR(bigint(r));
    return solve(bigint(l), onRight) + onRight + 1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
    bigint res = solveR(bigint(1));
    cout << "Answer " << res.tostring() << endl;
}
