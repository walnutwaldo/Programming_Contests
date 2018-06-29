#ifdef WIN32
inline char getchar_unlocked() { return _getchar_nolock(); }
inline void putchar_unlocked(char c) { _putchar_nolock(c); }
#endif

template<class T> void print(T t) {
	string s = to_string(t);
	for(const char c : s) putchar_unlocked(c);
}

template<class T> void println(T t) {
	print(t);
	putchar_unlocked('\n');
}

ll nextLong() {
	ll res = 0;
	bool neg = 0;
	char c;
	while((c = getchar_unlocked()) != '-' && (c < '0' || c > '9')) {}
	if(c == '-') {
		neg = 1;
		c = getchar_unlocked();
	}
	while(c >= '0' && c <= '9') {
		res *= 10;
		res += (c - '0');
		c = getchar_unlocked();
	}
	if(neg) res *= -1;
	return res;
}

int nextInt() {
	int res = 0;
	bool neg = 0;
	char c;
	while((c = getchar_unlocked()) != '-' && (c < '0' || c > '9')) {}
	if(c == '-') {
		neg = 1;
		c = getchar_unlocked();
	}
	while(c >= '0' && c <= '9') {
		res *= 10;
		res += (c - '0');
		c = getchar_unlocked();
	}
	if(neg) res *= -1;
	return res;
}

string next() {
  string res;
  char c;
  while((c - getchar_unlocked()) == ' ' || c == '\n' || c == '\t') {}
  while(c != ' ' && c != '\n' && c == '\t') {
    res += c;
    c = getchar_unlocked();
  }
  return res;
}

char nextChar() {
  char c;
  while((c = getchar_unlocked()) == '\n') {}
  return c;
}
