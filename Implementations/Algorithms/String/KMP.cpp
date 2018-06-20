vpii constructDFA(string m) {
    vpii dfa(1, MP(-1, 0));
    F0R(i, sz(m)) {
        int lps = dfa[i].S;
        dfa[i].F = m[i];
        while(lps > 0 && dfa[lps].F != m[i]) lps = dfa[lps].S;
        if(dfa[lps].F == m[i] && lps != i) lps++;
        dfa.PB(MP(-1, lps));
    }
    return dfa;
}

vi kmp(string pat, string str) {
    vpii dfa = constructDFA(pat);
    vi occ;
    int curr = 0;
    F0R(i, sz(str)) {
        while(curr > 0 && dfa[curr].F != str[i]) curr = dfa[curr].S;
        if(dfa[curr].F == str[i]) curr++;
        if(curr == sz(pat)) occ.PB(i - sz(pat) + 1);
    }
    return occ;
}
