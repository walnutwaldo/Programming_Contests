#include <bits/stdc++.h>
using namespace std;
int totalStart, totalEnd, s[4], e[4], promoted[4];
int main() {
    ifstream fin("promote.in");
    ofstream fout("promote.out");
    for(int i = 0; i < 4; i++) {
        fin >> s[i] >> e[i];
        totalStart += s[i];
        totalEnd += e[i];
    }
    promoted[0] = totalEnd - totalStart;
    for(int i = 1; i < 4; i++) {
        promoted[i] =  promoted[i - 1] + s[i - 1] - e[i - 1];
    }
    for(int i = 1; i < 4; i++) fout << promoted[i] << "\n";
}
