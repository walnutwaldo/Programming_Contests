int n, m, p, level[MAXN], match[MAXN];
vi adj[MAXN];
bool vis[MAXN];

bool dfs(int node) {
	if(vis[node]) return 0;
	vis[node] = 1;
	if(!level[node]) return 1;
	if(level[node] & 1) { for(const int next : adj[node]) if(level[next] == level[node] - 1 && dfs(next)) {
		match[node] = next;
		match[next] = node;
		return 1;
	}} else return dfs(match[node]);
	return 0;
}

int hopKarp(){
	int res = 0;
	F0R(i, n + m) match[i] = -1;
	while(1) {
		int free = 0, augPaths = 0;
		vi frees;
		queue<int> q;
		F0R(i, n + m) level[i] = ((i < n && match[i] == -1)?0:-1);
		memset(vis, 0, (n + m) * sizeof(bool));
		F0R(i, n) if(match[i] == -1) q.push(i);

		while(!q.empty()) {
			int curr = q.front(); q.pop();
			if(!free && (level[curr] & 1) && match[curr] == -1) free = level[curr];
			if(free && free == level[curr] && match[curr] == -1) frees.PB(curr); 
			if(free) continue;

			if(level[curr] & 1) {
				level[match[curr]] = level[curr] + 1;
				q.push(match[curr]);
			} else for(const int next : adj[curr]) if(level[next] == -1) {
				level[next] = level[curr] + 1;
				q.push(next);
			}			
		}
		for(const int i : frees) if(dfs(i)) augPaths++;
		if(!augPaths) return res;
		res += augPaths;
	}
}
