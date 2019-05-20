// 有向图最小生成树计数
struct node {
	int a, b, cost;
}edge[maxm];

int n, m, o;
ll ans, mod;
int pre[maxn], ka[maxn];
ll G[maxn][maxn], B[maxn][maxn];
bitset<maxn> vis;
vector<int> v[maxn];

bool cmp(node a, node b) { return a.cost < b.cost; }
int find(int x) { return pre[x] == x ? pre[x] : pre[x] = find(pre[x]); }

ll det(ll a[][maxn], int n) { //Matrix-Tree定理求Kirchhoff矩阵
	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++) a[i][j] %= mod;
	ll ret = 1;
	for (int i = 1; i<n; i++) {
		for (int j = i + 1; j<n; j++)
			while (a[j][i]) {
				ll t = a[i][i] / a[j][i];
				for (int k = i; k<n; k++) a[i][k] = (a[i][k] - a[j][k] * t) % mod;
				for (int k = i; k<n; k++) swap(a[i][k], a[j][k]);
				ret = -ret;
			}
		if (a[i][i] == 0) return 0;
		ret = ret * a[i][i] % mod;
	}
	return (ret + mod) % mod;
}

void Matrix_Tree() {
	for (int i = 1; i <= n; i++) { //根据访问标记找出连通分量
		if (vis[i]) {
			v[find(i)].push_back(i);
			vis[i] = 0;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (v[i].size() > 1) { //枚举连通分量
			memset(B, 0, sizeof(B));
			int len = v[i].size();
			for (int a = 0; a < len; a++) {
				for (int b = a + 1; b < len; b++) {
					int la = v[i][a], lb = v[i][b];
					B[b][a] -= G[la][lb];
					B[a][b] = B[b][a];
					B[a][a] += G[la][lb];
					B[b][b] += G[la][lb];
				} //构造矩阵
			}
			ll ret = det(B, len) % mod;
			ans = ans * ret % mod;
			for (int j = 0; j < len; j++)
				pre[v[i][j]] = i;
		}
	}
	for (int i = 1; i <= n; i++) { //连通图缩点+初始化
		pre[i] = find(i);
		ka[i] = pre[i];
		v[i].clear();
	}
}

int main()
{
	while (scanf("%d%d%lld", &n, &m, &mod), n || m || mod) {
		for (int i = 1; i <= m; i++)
			scanf("%d%d%d", &edge[i].a, &edge[i].b, &edge[i].cost);
		sort(edge + 1, edge + m + 1, cmp);
		for (int i = 1; i <= n; i++)
			v[i].clear();
		for (int i = 1; i <= n; i++)
			pre[i] = ka[i] = i;
		vis.reset();
		memset(G, 0, sizeof(G));
		ans = 1;
		o = edge[1].cost;
		for (int i = 1; i <= m; i++) {
			int pa = find(edge[i].a), pb = find(edge[i].b);
			if (pa != pb) {
				vis[pa] = 1;
				vis[pb] = 1;
				ka[find(pa)] = find(pb);
				G[pa][pb]++;
				G[pb][pa]++;
			}
			if (i == m || edge[i + 1].cost != o) { //所有相同的边并成一组
				Matrix_Tree();
				o = edge[i + 1].cost;
			}
		}
		bool done = true;
		for (int i = 2; i <= n; i++) {
			if (ka[i] != ka[i - 1]) {
				done = false;
				break;
			}
		}
		if (!done) printf("0\n");
		else {
			ans %= mod;
			printf("%lld\n", ans);
		}
	}
	return 0;
}