#include <bits/stdc++.h>
#include <unordered_set>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (a) - 1; i >= (b); i--)

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MAXN 500
#define MAXM 500

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, m;
string gene[2*MAXN];

ll valOf(char c) {
    int v = 0;
    switch(c) {
    case 'A':
        v++;
    case 'T':
        v++;
    case 'C':
        v++;
    }
    return v;
}

int main() {
    ifstream fin("cownomics.in");
    ofstream fout("cownomics.out");
    fin >> n >> m;
    F0R(i, 2 * n) {
        fin >> gene[i];
    }
    ll hashes[2 * n];
    F0R(i, 2*n) hashes[i] = valOf(gene[i].at(0));
    ll mult[m];
    mult[0] = 1;
    FOR(p, 1, m) {
        mult[p] = mult[p - 1] * 101;
    }
    int i = 0, j = 0, minimumLength = m;
    while(j < m) {
        unordered_set<ll> spotted;
        F0R(k, n) spotted.insert(hashes[k]);
        bool works = true;
        FOR(l, n, 2 * n) {
            if(spotted.count(hashes[l])) {
                works = false;
                j++;
                F0R(k, 2 * n) {
                    hashes[k]*=mult[1];
                    if(j < m) {
                        hashes[k]+=valOf(gene[k].at(j));
                    }
                }
                break;
            }
        }
        if(works) {
            minimumLength = min(minimumLength, j - i + 1);
            F0R(k, 2 * n) {
                hashes[k]-= mult[j - i] * valOf(gene[k].at(i));
            }
            i++;
            if(i > j) {
                j++;
                F0R(k, 2 * n) {
                    hashes[k]*=mult[1];
                    if(j < m) {
                        hashes[k]+=valOf(gene[k].at(j));
                    }
                }
            }
        }
    }
    fout << minimumLength << endl;
    return 0;
}
