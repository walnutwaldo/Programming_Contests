// Lowercase English Alphabet
vector<int*> constructDFA(string m) {
	vector<int*> dfa(1, new int[26]{0});
	F0R(i, sz(m)) {
		int lps = dfa[i][m[i] - 'a'];
		dfa[i][m[i] - 'a'] = i + 1;
		dfa.PB(new int[26]);
		copy(dfa[lps], dfa[lps] + 26, dfa.back());
	}
	return dfa;
}

vi kmp(string pat, string str) {
	vector<int*> dfa = constructDFA(pat);
	vi occ;
	int curr = 0;
	F0R(i, sz(str)) {
		curr = dfa[curr][str[i] - 'a'];
		if(curr == sz(pat)) occ.PB(i - sz(pat) + 1);
	}
	return occ;
}
