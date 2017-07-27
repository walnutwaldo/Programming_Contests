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

string s;
ll N;

int locOf(ll N) {
    if(N < s.length())
        return N;
    ll rep = N/s.length() + 1;
    ll powerUnder = exp2(ceil(log2(rep)) - 1);
    ll place = N - s.length() * (powerUnder);
    return locOf((place - 1 + powerUnder*s.length()) % (powerUnder*s.length()));
}

int main() {
    ifstream fin("cowcode.in");
    ofstream fout("cowcode.out");

    fin >> s >> N;

    fout << s[locOf(N - 1)];

    return 0;
}
