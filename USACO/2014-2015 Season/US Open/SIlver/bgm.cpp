#include <bits/stdc++.h>

#define F0R(i, a) for(int i = 0; i < a; i++)

using namespace std;

typedef long long ll;

int n;
ll res, b[7], e[7], s[7], i[7], g[7], o[7], m[7];

int main() {
    ifstream fin("bgm.in");
    ofstream fout("bgm.out");
    fin >> n;
    F0R(x, n) {
        char c;
        int v;
        fin >> c >> v;
        v = ((v % 7) + 7) % 7;
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
    F0R(B, 7) F0R(E, 7) F0R(S, 7) F0R(I, 7) F0R(G, 7) F0R(O, 7) F0R(M, 7) if((B+E+S+S+I+E) * (G+O+E+S) * (M+O+O) % 7 == 0) res += b[B] * e[E] * s[S] * i[I] * g[G] * o[O] * m[M];
    fout << res << endl;
}
