// 主席树求[l,r]第k大，可单点修改 使用树状数组套主席树在线操作，树状数组维护改变量
// M = maxn * 40;
int n, q, m, tot;
int A[maxn], T[maxn];
int tree[maxn], lson[M], rson[M], Cnt[M];
int Ntree[maxn], use[maxn];	// Ntree[i]表示动态第i棵树的树根, use[i]表示第i个树根是谁在使用

struct Query {
	int kind;
	int l, r, k;
}query[10005];

void Init_hash(int k) {
	sort(T, T + k);
	m = unique(T, T + k) - T;
}

int Hash(int x) { return lower_bound(T, T + m, x) - T; }

int build(int l, int r) {
	int root = tot++;
	Cnt[root] = 0;
	if (l != r) {
		int mid = (l + r) >> 1;
		lson[root] = build(l, mid);
		rson[root] = build(mid + 1, r);
	}
	return root;
}

int update(int root, int pos, int val) {
	int newroot = tot++, tmp = newroot;
	int l = 0, r = m - 1;
	Cnt[newroot] = Cnt[root] + val;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			lson[newroot] = tot++; rson[newroot] = rson[root];
			newroot = lson[newroot]; root = lson[root];
			r = mid;
		}
		else {
			rson[newroot] = tot++; lson[newroot] = lson[root];
			newroot = rson[newroot]; root = rson[root];
			l = mid + 1;
		}
		Cnt[newroot] = Cnt[root] + val;
	}
	return tmp;
}

inline int lowbit(int x) { return x & (-x); }

int sum(int x) {
	int ret = 0;
	while (x > 0) {
		ret += Cnt[lson[use[x]]];
		x -= lowbit(x);
	}
	return ret;
}

void Modify(int x, int pos, int val) {
	while (x <= n) {
		Ntree[x] = update(Ntree[x], pos, val);
		x += lowbit(x);
	}
}

int Query(int left, int right, int k) {
	int lrt = tree[left - 1];
	int rrt = tree[right];
	int l = 0, r = m - 1;
	for (int i = left - 1; i; i -= lowbit(i)) use[i] = Ntree[i];
	for (int i = right; i; i -= lowbit(i)) use[i] = Ntree[i];
	while (l < r) {
		int mid = (l + r) >> 1;
		// sum(right) - sum(left - 1)为改变量，Cnt[lson[rrt]] - Cnt[lson[lrt]]为基础差值
		int tmp = sum(right) - sum(left - 1) + Cnt[lson[rrt]] - Cnt[lson[lrt]];
		if (tmp >= k) {
			r = mid;
			for (int i = left - 1; i; i -= lowbit(i))
				use[i] = lson[use[i]];
			for (int i = right; i; i -= lowbit(i))
				use[i] = lson[use[i]];
			lrt = lson[lrt];
			rrt = lson[rrt];
		}
		else {
			l = mid + 1;
			k -= tmp;
			for (int i = left - 1; i; i -= lowbit(i))
				use[i] = rson[use[i]];
			for (int i = right; i; i -= lowbit(i))
				use[i] = rson[use[i]];
			lrt = rson[lrt];
			rrt = rson[rrt];
		}
	}
	return l;
}

int main()
{
	int Tcase;
	char op[10];
	scanf("%d", &Tcase);
	while (Tcase--) {
		scanf("%d%d", &n, &q);
		tot = 0; m = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &A[i]);
			T[m++] = A[i];
		}
		for (int i = 0; i < q; i++) {
			scanf("%s", op);
			if (op[0] == 'Q') {
				query[i].kind = 0;
				scanf("%d%d%d", &query[i].l, &query[i].r, &query[i].k);
			}
			else {
				query[i].kind = 1;
				scanf("%d%d", &query[i].l, &query[i].r);
				T[m++] = query[i].r;
			}
		}
		Init_hash(m);
		tree[0] = build(0, m - 1);
		for (int i = 1; i <= n; i++)
			tree[i] = update(tree[i - 1], Hash(A[i]), 1);
		for (int i = 1; i <= n; i++) Ntree[i] = tree[0];
		for (int i = 0; i < q; i++) {
			if (query[i].kind == 0)
				printf("%d\n", T[Query(query[i].l, query[i].r, query[i].k)]);
			else {
				Modify(query[i].l, Hash(A[query[i].l]), -1);
				Modify(query[i].l, Hash(query[i].r), 1);
				A[query[i].l] = query[i].r;
			}
		}
	}
	return 0;
}