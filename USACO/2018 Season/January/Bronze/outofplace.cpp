#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

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
#define R real()
#define I image()
#define PI acos(-1)
#define MAXN 100

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;
typedef complex<ld> cld;

int n, a[MAXN];

bool works(int idx) {
    vi v;
    F0R(i, n) if(i != idx) v.PB(a[i]);
    F0R(i, n - 2) if(v[i] > v[i + 1]) return 0;
    return 1;
}

int main() {
    ifstream fin("outofplace.in");
    ofstream fout("outofplace.out");
    fin >> n;
    F0R(i, n) fin >> a[i];
    int i = -1;
    F0R(j, n) if(works(j)) i = j;
    if(i == -1) {
        fout << 0 << endl;
        return 0;
    }
    if(i < n - 1 && a[i] > a[i + 1]) {
        int res = 0;
        int j = i + 1;
        while(j < n && a[j] < a[i]) {
            if(j == i + 1 || a[j] != a[j - 1]) res++;
            j++;
        }
        fout << res << endl;
        return 0;
    } else if (i > 0 && a[i] < a[i - 1]) {
        int res = 0;
        int j = i - 1;
        while(j >= 0 && a[j] > a[i]) {
            if(j == i - 1 || a[j] != a[j + 1]) res++;
            j--;
        }
        fout << res << endl;
        return 0;
    }
    return 0;
}
