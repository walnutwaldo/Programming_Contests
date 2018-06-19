vector<int*> constructDFA(string m) {
	vector<int*> dfa(1, new int[128]{0});
	F0R(i, sz(m)) {
		int lps = dfa[i][m[i]];
		dfa[i][m[i]] = i + 1;
		dfa.PB(new int[128]);
		copy(dfa[lps], dfa[lps] + 128, dfa.back());
	}
	return dfa;
}

vi kmp(string pat, string str) {
	vector<int*> dfa = constructDFA(pat);
	vi occ;
	int curr = 0;
	F0R(i, sz(str)) {
		curr = dfa[curr][str[i]];
		if(curr == sz(pat)) occ.PB(i - sz(pat) + 1);
	}
	return occ;
}
