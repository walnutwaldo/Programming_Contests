#include <bits/stdc++.h>
using namespace std;
int a, b, c, d;
int main() {
    ifstream fin("paint.in");
    ofstream fout("paint.out");
    fin >> a >> b >> c >> d;
    if(c >= b || d <= a) fout << (b - a) + (d - c) << "\n";
    else fout << max(d,b)  - min(a , c) << "\n";
    return 0;
}
