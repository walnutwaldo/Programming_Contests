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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<ull> vul;
typedef complex<ld> point;

char grid[3][3];

set<char> individuals;
set<pair<char, char>> teams;

int numDiff(char x, char y, char z) {
	if(y != x && z != x && z != y) return 3;
	else if(y != x || z != x) return 2;
	return 1;
}

pair<char, char> minMax(char x, char y, char z){
	return MP(min(x, min(y, z)), max(x, max(y, z)));
}

int main() {
	ifstream fin("tttt.in");
	ofstream fout("tttt.out");
	F0R(i, 3) F0R(j, 3) fin >> grid[i][j];
	F0R(i, 3) if(numDiff(grid[i][0], grid[i][1], grid[i][2]) == 1) individuals.insert(grid[i][0]);
	F0R(i, 3) if(numDiff(grid[0][i], grid[1][i], grid[2][i]) == 1) individuals.insert(grid[0][i]);
	if(numDiff(grid[0][0], grid[1][1], grid[2][2]) == 1) individuals.insert(grid[0][0]);
	if(numDiff(grid[2][0], grid[1][1], grid[0][2]) == 1) individuals.insert(grid[2][0]);
	
	F0R(i, 3) if(numDiff(grid[i][0], grid[i][1], grid[i][2]) == 2)
		teams.insert(minMax(grid[i][0], grid[i][1], grid[i][2]));
	F0R(i, 3) if(numDiff(grid[0][i], grid[1][i], grid[2][i]) == 2) 
		teams.insert(minMax(grid[0][i], grid[1][i], grid[2][i]));
	if(numDiff(grid[0][0], grid[1][1], grid[2][2]) == 2)
		teams.insert(minMax(grid[0][0], grid[1][1], grid[2][2]));
	if(numDiff(grid[2][0], grid[1][1], grid[0][2]) == 2)
		teams.insert(minMax(grid[2][0], grid[1][1], grid[0][2]));
	fout << individuals.size() << endl << teams.size() << endl;
}
