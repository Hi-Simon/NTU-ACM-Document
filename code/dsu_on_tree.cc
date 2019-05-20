// 树上启发式合并：dsu on tree
int n, x, y, Son, Max;
int sz[maxn], son[maxn];
ll sum, ans[maxn];
vector<int> v[maxn];

void getson(int u, int fa) {
	sz[u] = 1;
	for (int i = 0; i < v[u].size(); i++) {
		int to = v[u][i];
		if (to != fa) {
			getson(to, u);
			sz[u] += sz[to];
			if (sz[to] > sz[son[u]])
				son[u] = to;
		}
	}
}

void add(int u, int fa, int val) {
	// 更新节点数据
	// cnt[attr[u]] += val;
	for (int i = 0; i < v[u].size(); i++) {
		int to = v[u][i];
		if (to != fa && to != Son)
			add(to, u, val);
	}
}

void dfs(int u, int fa, int k) {
	for (int i = 0; i < v[u].size(); i++) {
		int to = v[u][i];
		if (to != fa && to != son[u])
			dfs(to, u, 0);
	}
	if (son[u]) dfs(son[u], u, 1), Son = son[u];
	add(u, fa, 1); Son = 0;
	// 此处统计u节点处答案
	// ans[u] = sum;
	if (!k) add(u, fa, -1), Max = sum = 0;
}

// getson(1, 0);
// dfs(1, 0, 0);