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
#define MAXC 250

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<ull> vul;
typedef complex<ld> point;

int n, aID, bID, parent[MAXC], depth[MAXC];
string a, b;
unordered_map<string, int> id;
vi children[MAXC];

int getID(string s) {
	if(!id.count(s)) {
		int newID = id.size();
		id[s] = newID;
	}
	return id[s];
}

void dfs(int node, int d) {
	depth[node] = d;
	for(auto next : children[node]) dfs(next, d + 1);
}

int lca(int a, int b) {
	if(depth[a] < depth[b]) swap(a, b);
	while(depth[a] > depth[b]) a = parent[a];
	while(a != b) {
		a = parent[a];
		b = parent[b];
	}
	return a;
}

int main() {
	ifstream fin("family.in");
	ofstream fout("family.out");
	fin >> n >> a >> b;
	aID = getID(a), bID = getID(b);
	F0R(i, MAXC) parent[i] = -1;
	F0R(i, n) {
		string mother, child;
		fin >> mother >> child;
		int mID = getID(mother), cID = getID(child);
		children[mID].PB(cID);
		parent[cID] = mID;
	}
	for(auto p : id) if(parent[p.S] == -1) dfs(p.S, 0);
	int commonAnc = lca(aID, bID);
	if(commonAnc == -1) fout << "NOT RELATED" << endl;
	else {
		int da = depth[aID], db = depth[bID], dc = depth[commonAnc];
		if(da - dc > 1 && db - dc > 1) fout << "COUSINS" << endl;
		else if(da - dc == 1 && db - dc == 1) fout << "SIBLINGS" << endl;
		else if(bID == commonAnc) {
			int diff = da - db;
			fout << b << " is the ";
			if(diff == 1) fout << "mother of " << a << endl;
			else {
				FOR(i, 2, diff) fout << "great-";
				fout << "grand-mother of " << a << endl;
			}
		} else if(aID == commonAnc) {
			int diff = db - da;
			fout << a << " is the ";
			if(diff == 1) fout << "mother of " << b << endl;
			else {
				FOR(i, 2, diff) fout << "great-";
				fout << "grand-mother of " << b << endl;
			}
		} else if(db - dc == 1){
			int diff = da - dc;
			fout << b << " is the ";
			FOR(i, 2, diff) fout << "great-";
			fout << "aunt of " << a << endl;
		} else {
			int diff = db - dc;
			fout << a << " is the ";
			FOR(i, 2, diff) fout << "great-";
			fout << "aunt of " << b << endl;
		}
	}
}
