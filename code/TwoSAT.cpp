struct TwoSAT {
	const static int maxm = maxn * 2;
	int N, c;
	int S[maxm], vis[maxm];
	vector<int> G[maxm];
	bool DFS(int u) {
		if (vis[u ^ 1]) return false;
		if (vis[u]) return true;
		vis[u] = 1;
		S[c++] = u;
		for (int i = 0; i < G[u].size(); i++)
			if (!DFS(G[u][i])) return false;
		return true;
	}
	void Clear() {
		for (int i = 0; i < N * 2; i++)
			G[i].clear();
		memset(vis, 0, sizeof(vis));
	}
	void AddClause(int x, int y) {	// x, y 为矛盾对
		G[x].push_back(y ^ 1);
		G[y].push_back(x ^ 1);
	}
	bool Solve() {
		for (int i = 0; i < N * 2; i += 2)
			if (!vis[i] && !vis[i ^ 1]) {
				c = 0;
				if (!DFS(i)) {
					while (c > 0)
						vis[S[--c]] = 0;
					if (!DFS(i ^ 1))
						return false;
				}
			}
		return true;
	}
};