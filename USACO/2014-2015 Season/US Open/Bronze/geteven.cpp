#include <bits/stdc++.h>

#define F0R(i, a) for(int i = 0; i < a; i++)

using namespace std;

typedef long long ll;

int n;
ll res, b[2], e[2], s[2], i[2], g[2], o[2], m[2];

int main() {
    ifstream fin("geteven.in");
    ofstream fout("geteven.out");
    fin >> n;
    F0R(x, n) {
        char c;
        int v;
        fin >> c >> v;
        v = ((v % 2) + 2) % 2;
        switch(c){
            case 'B': b[v]++; break;
            case 'E': e[v]++; break;
            case 'S': s[v]++; break;
            case 'I': i[v]++; break;
            case 'G': g[v]++; break;
            case 'O': o[v]++; break;
            case 'M': m[v]++; break;
        }
    }
    F0R(B, 2) F0R(E, 2) F0R(S, 2) F0R(I, 2) F0R(G, 2) F0R(O, 2) F0R(M, 2) if((B+E+S+S+I+E) * (G+O+E+S) * (M+O+O) % 2 == 0) res += b[B] * e[E] * s[S] * i[I] * g[G] * o[O] * m[M];
    fout << res << endl;
}
