struct AhoTrie{

	int currNode = 0, numPats, numNodes = 0;
	vector<map<char, int>> trie;
	vi dict, link;
	vector<vpii> strData;

	AhoTrie(const vector<string> &pat) {
		numPats = sz(pat);
		addNode();
		F0R(i, sz(pat)) {
			int curr = 0;
			for(const char c : pat[i]) {
				if(!trie[curr].count(c)) trie[curr].insert(MP(c, numNodes)), addNode();
				curr = trie[curr][c];
			}
			dict[curr] = curr; strData[curr].PB(MP(i, sz(pat[i])));
		}
		bfs();
	}
	
	void addNode() {
		numNodes++;
		dict.PB(0); link.PB(0); strData.PB(vpii()); trie.PB(map<char, int>());
	}

	void bfs() {
		queue<int> q;
		q.push(0);
		while(!q.empty()) {
			int i = q.front(); q.pop();
			for(const pair<char, int> p : trie[i]) {
				q.push(p.S);
				int lps = link[i];
				while(lps && !trie[lps].count(p.F)) lps = link[lps];
				if(trie[lps].count(p.F) && lps != i) lps = trie[lps][p.F];
				link[p.S] = lps;
				if(!dict[p.S]) dict[p.S] = dict[lps];
			}
		}	
	}
	
	void step(char c) {
		while(currNode && !trie[currNode].count(c)) currNode = link[currNode];
		if(trie[currNode].count(c)) currNode = trie[currNode][c];
	}
	
	void addToOcc(vector<vi> &occ, int idx) {
		int curr = dict[currNode];
		while(curr) {
			for(const pii p : strData[curr]) occ[p.F].PB(idx - p.S + 1);
			curr = dict[link[curr]];
		}
	}

	vector<vi> getOcc(const string &txt) {
		vector<vi> occ;
		F0R(i, numPats) occ.PB(vi());
		F0R(i, sz(txt)) {
			step(txt[i]);
			addToOcc(occ, i);
		}
		return occ;
	}

};
