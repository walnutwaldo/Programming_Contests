vi z(string s) {
  vi res(sz(s));
  int lo = 0, hi = 0;
  FOR(i, 1, sz(s)) {
    res[i] = max(0, min(hi - i + 1, res[i - lo]));
    while(i + z[i] < sz(s) && s[i + z[i]] == s[z[i]]) lo = i, hi = i + z[i]++;
  }
  return res;
}
