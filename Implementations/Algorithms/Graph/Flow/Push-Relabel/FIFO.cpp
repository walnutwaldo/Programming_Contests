int n, m, h[MAXN], curr[MAXN];
ll e[MAXN], c[MAXN][MAXN], f[MAXN][MAXN];
vi neigh[MAXN];
queue<int> overflows;

ll cf(int u, int v) { return c[u][v] - f[u][v]; }

void initPreflow(int s, int t) {
	h[s] = n;
	F0R(i, n) if(c[s][i]) {
		f[s][i] = c[s][i]; f[i][s] = -c[s][i];
		e[i] += c[s][i]; e[s] -= c[s][i];
		overflows.push(i);
	}
}

void push(int u, int v) {
	int flow = min(e[u], cf(u, v));
	f[u][v] += flow; f[v][u] -= flow;
	e[u] -= flow; e[v] += flow;
	if(e[v] == flow) overflows.push(v);
}

void relabel(int node) {
	int mn = INT_MAX;
	F0R(i, n) if(cf(node, i) > 0) mn = min(mn, h[i]);
	h[node] = mn + 1;
}

void discharge(int u) {
	while(e[u]) {
		int v = curr[u];
		if(v == sz(neigh[u])){
			relabel(u);
			curr[u] = 0;
		} else if (cf(u, neigh[u][v]) && h[u] == h[neigh[u][v]] + 1) push(u, neigh[u][v]);
		else curr[u]++;
	}
}

ll flow(int s, int t) {
	initPreflow(s, t);
	F0R(i, n) F0R(j, n) if(c[i][j] || c[j][i]) neigh[i].PB(j);
	while(!overflows.empty()) {
		int node = overflows.front(); overflows.pop();
		if(node == s || node == t) continue;
		discharge(node);
	}
	return e[t];
}
