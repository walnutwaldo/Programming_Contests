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

int n;
string names[7] {"Bessie", "Elsie", "Daisy", "Gertie", "Annabelle", "Maggie", "Henrietta"};
unordered_map<string, int> production;

int main() {
    ifstream fin("notlast.in");
    ofstream fout("notlast.out");

    fin >> n;
    F0R(i, 7) production[names[i]] = 0;
    F0R(i, n) {
        string s;
        int p;
        fin >> s >> p;
        production[s] += p;
    }
    int minP = production[names[0]];
    F0R(i, 7) minP = min(minP, production[names[i]]);
    string second = "";
    F0R(i, 7) {
        if(production[names[i]] > minP && (second == "" || production[names[i]] <= production[second])) {
            if(second != "" && production[second] == production[names[i]]) {
                fout << "Tie\n";
                return 0;
            }
            second = names[i];
        }
    }
    if(second == "") fout << "Tie\n";
    else fout << second << endl;
    return 0;
}
