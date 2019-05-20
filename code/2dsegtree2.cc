// 二维线段树区间加值+单点查询 树套树实现
int n;
int x2rt[maxn], y2rt[maxn];

struct Nodey {
	int l, r;
	int val;
};

struct Nodex {
	int l, r;
	Nodey nodey[maxn << 2];

	void build(int l, int r, int rt) {
		nodey[rt].l = l;
		nodey[rt].r = r;
		nodey[rt].val = 0;
		if (l == r) {
			y2rt[l] = rt;
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid, rt << 1);
		build(mid + 1, r, rt << 1 | 1);
	}

	void addVal(int rt, int L, int R, int val) {
		if (nodey[rt].l == L && nodey[rt].r == R) {
			nodey[rt].val += val;
			return;
		}
		int mid = (nodey[rt].l + nodey[rt].r) >> 1;
		if (R <= mid) addVal(rt << 1, L, R, val);
		else if (L > mid) addVal(rt << 1 | 1, L, R, val);
		else {
			addVal(rt << 1, L, mid, val);
			addVal(rt << 1 | 1, mid + 1, R, val);
		}
	}
}nodex[maxn << 2];

void build(int l, int r, int rt) {
	nodex[rt].l = l;
	nodex[rt].r = r;
	nodex[rt].build(1, n, 1);
	if (l == r) {
		x2rt[l] = rt;
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, rt << 1);
	build(mid + 1, r, rt << 1 | 1);
}

void addVal(int rt, int x1, int x2, int y1, int y2, int val) {
	if (nodex[rt].l == x1 && nodex[rt].r == x2) {
		nodex[rt].addVal(1, y1, y2, val);
		return;
	}
	int mid = (nodex[rt].l + nodex[rt].r) >> 1;
	if (x2 <= mid) addVal(rt << 1, x1, x2, y1, y2, val);
	else if (x1 > mid) addVal(rt << 1 | 1, x1, x2, y1, y2, val);
	else {
		addVal(rt << 1, x1, mid, y1, y2, val);
		addVal(rt << 1 | 1, mid + 1, x2, y1, y2, val);
	}
}

int getVal(int x, int y) {
	int ret = 0;
	for (int i = x2rt[x]; i; i >>= 1)
		for (int j = y2rt[y]; j; j >>= 1)
			ret += nodex[i].nodey[j].val;
	return ret;
}