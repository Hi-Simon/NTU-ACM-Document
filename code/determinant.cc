// 无向图，求生成树个数 Determinant算法
ll A[maxn][maxn], B[maxn][maxn];
ll determinant(int n) {
	ll res = 1;
	for (int i = 1; i <= n; i++) {
		if (!B[i][i]) {
			bool flag = false;
			for (int j = i + 1; j <= n; j++) {
				if (B[j][i]) {
					flag = true;
					for (int k = i; k<n; k++)
						swap(B[i][k], B[j][k]);
					res = -res;
					break;
				}
			}
			if (!flag) return 0;
		}
		for (int j = i + 1; j <= n; j++) {
			while (B[j][i]) {
				ll t = B[i][i] / B[j][i];
				for (int k = i; k <= n; k++) {
					B[i][k] = B[i][k] - t * B[j][k];
					swap(B[i][k], B[j][k]);
				}
				res = -res;
			}
		}
		res *= B[i][i];
	}
	return res;
}
int main()
{
	int n, m, k;
	while (~scanf("%d%d%d", &n, &m, &k)) {
		memset(A, 0, sizeof(A));
		memset(B, 0, sizeof(B));
		for (int i = 1; i <= m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			A[a][b] = A[b][a] = 1;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (i != j && !A[i][j]) {
					B[i][i]++;
					B[i][j] = -1;
				}
			}
		}
		n--;
		ll ans = determinant(n);
		printf("%lld\n", ans);
	}
}