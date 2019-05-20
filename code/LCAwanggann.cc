// LCA ST算法
int n, top, root;
int a[maxn << 1], d[maxn], st[maxn];
int f[maxn << 1][18], loc[maxn << 1][18];
vector<int> v[maxn];

int log2(int x) {
	int k = 0;
	while (x > 1) {
		x /= 2;
		k++;
	}
	return k;
}

void dfs(int u, int dep) {
	d[u] = dep;
	a[++top] = u;
	for (int i = 0; i<=v[u].size(); i++) {
		int to = v[u][i];
		dfs(to, dep + 1);
		a[++top] = u;
	}
}

void init() {
	int s = log2(top);
	for (int i = 1; i <= top; i++) {
		f[i][0] = d[a[i]];
		loc[i][0] = a[i];
	}
	for (int j = 1; j <= s; j++) {
		int k = top - (1 << j) + 1;
		for (int i = 1; i <= k; i++) {
			int x = i + (1 << (j - 1));
			if (f[i][j - 1] <= f[x][j - 1]) {
				f[i][j] = f[i][j - 1];
				loc[i][j] = loc[i][j - 1];
			}
			else {
				f[i][j] = f[x][j - 1];
				loc[i][j] = loc[x][j - 1];
			}
		}
	}
}

int query(int x, int y) {
	x = st[x], y = st[y];
	if (x > y) swap(x, y);
	int i = log2(y - x);
	int k = y - (1 << i) + 1;
	return f[x][i] < f[k][i] ? loc[x][i] : loc[k][i];
}

//===============================================================================

// LCA Tarjan算法
int n, root, cnt;
int pre[maxn], ans[maxn];
vector<int> v[maxn], s[maxn], num[maxn];

int find(int x) { return pre[x] == x ? x : pre[x] = find(pre[x]); }

void dfs(int u) {
	pre[u] = u;
	for (int i = 0; i < v[u].size(); i++) {
		int to = v[u][i];
		dfs(to);
		pre[find(pre[to])] = find(pre[u]);
	}
	for (int i = 0; i < s[u].size(); i++) {
		int to = s[u][i];
		if (pre[to] != to)
			ans[num[u][i]] = find(pre[to]);
	}
}

/*
for (int i = 1; i <= q; i++) {
	scanf("%d%d", &x, &y);
	if (x == y) ans[i] = x;
	s[x].push_back(y);
	s[y].push_back(x);
	num[x].push_back(i);
	num[y].push_back(i);
}
dfs(root);
*/

//=============================================================================

// LCA 倍增算法
int n, ma, root;
int d[maxn], f[maxn][20];
vector<int> v[maxn];
inline void dfs(int u, int dep, int fa) {
	d[u] = dep;
	f[u][0] = fa;
	ma = max(ma, dep);
	for (int i = 0; i < v[u].size(); i++)
		if (v[u][i] != fa) dfs(v[u][i], dep + 1, u);
}
inline int log2(int x) {
	int k = 0;
	while (x > 1) {
		x >>= 1;
		k++;
	}
	return k;
}
inline void init() {
	dfs(root, 0, 0);
	int s = log2(ma);
	for (int j = 1; j <= s; j++)
		for (int i = 1; i <= n; i++)
			f[i][j] = f[f[i][j - 1]][j - 1];
}
// 求x与y的LCA
inline int query(int x, int y) {
	if (d[x] < d[y]) swap(x, y);
	int s = log2(d[x] - d[y]);
	while (d[x] > d[y]) {
		if (d[x] - (1 << s) >= d[y])
			x = f[x][s];
		s--;
	}
	s = log2(d[x]);
	while (s > -1) {
		if (f[x][s] != f[y][s]) {
			x = f[x][s];
			y = f[y][s];
		}
		s--;
	}
	return x == y ? x : f[x][0];
}
// 判断a与p是否在同一树边上（p在a上方）
inline bool check(int a, int p) {
	if (d[a] < d[p]) return false;
	if (d[a] == d[p]) return a == p;
	int s = log2(d[a] - d[p]);
	while (d[a] > d[p]) {
		if (d[a] - (1 << s) >= d[p])
			a = f[a][s];
		s--;
	}
	return a == p;
}
// 求一条树边上x到y的距离
inline int getlen(int x, int y) {
	int ret = 0;
	if (d[x] < d[y]) swap(x, y);
	int s = log2(d[x] - d[y]);
	while (d[x] > d[y]) {
		if (d[x] - (1 << s) >= d[y]) {
			ret += (1 << s);
			x = f[x][s];
		}
		s--;
	}
	return ret;
}