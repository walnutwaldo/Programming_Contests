template<class T> void print(T t) {
    string s = to_string(t);
    for(const char c : s) _putchar_nolock(c);
}

template<class T> void println(T t) {
    print(t);
    _putchar_nolock('\n');
}

ll nextLong() {
    ll res = 0;
    bool neg = 0;
    char c;
    while((c = _getchar_nolock()) != '-' && (c < '0' || c > '9')) {}
    if(c == '-') {
        neg = 1;
        c = _getchar_nolock();
    }
    while(c >= '0' && c <= '9') {
        res *= 10;
        res += (c - '0');
        c = _getchar_nolock();
    }
    if(neg) res *= -1;
    return res;
}

int nextInt() {
    int res = 0;
    bool neg = 0;
    char c;
    while((c = _getchar_nolock()) != '-' && (c < '0' || c > '9')) {}
    if(c == '-') {
        neg = 1;
        c = _getchar_nolock();
    }
    while(c >= '0' && c <= '9') {
        res *= 10;
        res += (c - '0');
        c = _getchar_nolock();
    }
    if(neg) res *= -1;
    return res;
}

string next() {
  string res;
  char c;
  while((c - _getchar_nolock()) == ' ' || c == '\n' || c == '\t') {}
  while(c != ' ' && c != '\n' && c == '\t') {
    res += c;
    c = _getchar_nolock();
  }
  return res;
}

char nextChar() {
  char c;
  while((c = _getchar_nolock()) == '\n') {}
  return c;
}
