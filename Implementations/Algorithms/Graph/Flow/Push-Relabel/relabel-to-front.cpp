// Uses LinkedList.cpp

int n, m, h[MAXN];
ll e[MAXN], c[MAXN][MAXN], f[MAXN][MAXN];
LinkedList<int> neigh[MAXN];
Node<int>* curr[MAXN];

ll cf(int u, int v) { return c[u][v] - f[u][v]; }

void initPreflow(int s, int t) {
	h[s] = n;
	F0R(i, n) if(c[s][i]) {
		f[s][i] = c[s][i]; f[i][s] = -c[s][i];
		e[i] += c[s][i]; e[s] -= c[s][i];
	}
}

void push(int u, int v) {
	int flow = min(e[u], cf(u, v));
	f[u][v] += flow; f[v][u] -= flow;
	e[u] -= flow; e[v] += flow;
}

void relabel(int node) {
	int mn = INT_MAX;
	F0R(i, n) if(cf(node, i) > 0) mn = min(mn, h[i]);
	h[node] = mn + 1;
}

void discharge(int u) {
	while(e[u]) {
		Node<int> *v = curr[u];
		if(!v){
			relabel(u);
			curr[u] = neigh[u].head;
		} else if (cf(u, v->val) && h[u] == h[v->val] + 1) push(u, v->val);
		else curr[u] = v->next;
	}
}

ll flow(int s, int t) {
	initPreflow(s, t);
	F0R(i, n) F0R(j, n) if(c[i][j] || c[j][i]) neigh[i].push(j);
	F0R(i, n) curr[i] = neigh[i].head;
	LinkedList<int> L;
	F0R(i, n) if(i != s && i != t) L.push(i);
	Node<int> *it = L.head;
	while(it) {
		int node = it->val;
		int sh = h[node];
		discharge(node);
		if(h[node] > sh) L.moveToFront(it);
		it = it->next;	
	}
	return e[t];
}
