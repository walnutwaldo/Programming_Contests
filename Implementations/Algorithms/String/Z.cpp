vi z(string s) {
  vi z(sz(s));
  int lo = 0, hi = 0;
  FOR(i, 1, sz(s)) {
    z[i] = max(0, min(hi - i + 1, z[i - lo]));
    while(i + z[i] < sz(s) && s[i + z[i]] == s[z[i]]) lo = i, hi = i + z[i]++;
  }
  return res;
}
