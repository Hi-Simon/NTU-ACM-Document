// 主席树 支持查询[l,r]区间第k大，以及区间内不重复数字个数
// M = maxn * 30;
int n, q, m, tot;	// n为数组大小，m为离散化后数组大小
int A[maxn], T[maxn];	// A为原数组，T为离散化数组
int tree[M], lson[M], rson[M], Cnt[M];	// Cnt[i]表示节点i的子树包含数字的总数

void Init_hash() {
	for (int i = 1; i <= n; i++) T[i] = A[i];
	sort(T + 1, T + n + 1);
	m = unique(T + 1, T + n + 1) - T - 1;
}

inline int Hash(int x) { return lower_bound(T + 1, T + m + 1, x) - T; }

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
	Cnt[newroot] = Cnt[root] + val;
	int l = 1, r = m;
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

void init() {	// 查询l~r第k大
	Init_hash();
	tree[0] = build(1, m);
	for (int i = 1; i <= n; i++) {
		int pos = Hash(A[i]);
		tree[i] = update(tree[i - 1], pos, 1);
	}
}

int query(int lrt, int rrt, int k) {	// 查询l~r第k大：T[query(tree[l - 1], tree[r], k)]
	int l = 1, r = m;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (Cnt[lson[rrt]] - Cnt[lson[lrt]] >= k) {
			r = mid;
			lrt = lson[lrt];
			rrt = lson[rrt];
		}
		else {
			l = mid + 1;
			k -= Cnt[lson[rrt]] - Cnt[lson[lrt]];
			lrt = rson[lrt];
			rrt = rson[rrt];
		}
	}
	return l;
}

void init() {	// 查询l~r内不重复数字个数
	tree[0] = build(1, n);
	map<int, int>mp;
	for (int i = 1; i <= n; i++) {
		if (mp.find(A[i]) == mp.end())
			tree[i] = update(tree[i - 1], i, 1);
		else {
			int tmp = update(tree[i - 1], mp[A[i]], -1);
			tree[i] = update(tmp, i, 1);
		}
		mp[A[i]] = i;
	}
}

int query(int root, int pos) {	// 查询l~r内不重复数字个数：query(tree[r], l)
	int ret = 0;
	int l = 1, r = n;
	while (pos > l) {
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			ret += Cnt[rson[root]];
			root = lson[root];
			r = mid;
		}
		else {
			root = rson[root];
			l = mid + 1;
		}
	}
	return ret + Cnt[root];
}