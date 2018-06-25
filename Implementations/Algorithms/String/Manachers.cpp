vi manachers(string s) {
	string t; t.reserve(2 * sz(s) + 1);
	F0R(i, sz(s)) t += '.', t += s[i];
	t[0] = 's'; t += 'e';
	vi res(sz(t));
	int lo = 0, hi = 0;
	FOR(i, 1, sz(t) - 1) {
		res[i] = max(0, min(hi - i, (i <= hi)?res[lo + hi - i]:0));
		while(t[i + res[i] + 1] == t[i - res[i] - 1]) res[i]++;
		if(i + res[i] > hi) hi = i + res[i], lo = i - res[i];
	}
	F0R(i, sz(s)) res[(i << 1) | 1] |= 1;
	F0R(i, sz(s) + 1) if(res[i << 1] & 1) res[i << 1]++;
	return res;
}
