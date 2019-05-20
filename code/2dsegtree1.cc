// 二维线段树单点更新+区间最值 树套树实现
int n;
int y2rt[maxn], x2rt[maxn];

struct Nodey {
	int l, r;
	int Max, Min;
};

struct Nodex {
	int l, r;
	Nodey nodey[maxn << 2];
	
	void build(int l, int r, int rt) {
		nodey[rt].l = l;
		nodey[rt].r = r;
		nodey[rt].Max = -inf;
		nodey[rt].Min = inf;
		if (l == r) {
			y2rt[l] = rt;
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid, rt << 1);
		build(mid + 1, r, rt << 1 | 1);
	}
	
	int queryMin(int rt, int L, int R) {
		if (nodey[rt].l == L && nodey[rt].r == R)
			return nodey[rt].Min;
		int mid = (nodey[rt].l + nodey[rt].r) >> 1;
		if (R <= mid) return queryMin(rt << 1, L, R);
		else if (L > mid) return queryMin(rt << 1 | 1, L, R);
		else return min(queryMin(rt << 1, L, mid), queryMin(rt << 1 | 1, mid + 1, R));
	}
	
	int queryMax(int rt, int L, int R) {
		if (nodey[rt].l == L && nodey[rt].r == R)
			return nodey[rt].Max;
		int mid = (nodey[rt].l + nodey[rt].r) >> 1;
		if (R <= mid) return queryMax(rt << 1, L, R);
		else if (L > mid) return queryMax((rt << 1) | 1, L, R);
		else return max(queryMax(rt << 1, L, mid), queryMax((rt << 1) | 1, mid + 1, R));
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

// 点修改
void update(int x, int y, int val) {
	int rtx = x2rt[x];
	int rty = y2rt[y];
	nodex[rtx].nodey[rty].Min = nodex[rtx].nodey[rty].Max = val;
	for (int i = rtx; i; i >>= 1) {
		for (int j = rty; j; j >>= 1) {
			if (i == rtx && j == rty)continue;
			if (j == rty) {
				nodex[i].nodey[j].Min = min(nodex[i << 1].nodey[j].Min, nodex[(i << 1) | 1].nodey[j].Min);
				nodex[i].nodey[j].Max = max(nodex[i << 1].nodey[j].Max, nodex[(i << 1) | 1].nodey[j].Max);
			}
			else {
				nodex[i].nodey[j].Min = min(nodex[i].nodey[j << 1].Min, nodex[i].nodey[(j << 1) | 1].Min);
				nodex[i].nodey[j].Max = max(nodex[i].nodey[j << 1].Max, nodex[i].nodey[(j << 1) | 1].Max);
			}
		}
	}
}

int queryMin(int rt, int x1, int x2, int y1, int y2) {
	if (nodex[rt].l == x1 && nodex[rt].r == x2)
		return nodex[rt].queryMin(1, y1, y2);
	int mid = (nodex[rt].l + nodex[rt].r) >> 1;
	if (x2 <= mid)return queryMin(rt << 1, x1, x2, y1, y2);
	else if (x1 > mid)return queryMin(rt << 1 | 1, x1, x2, y1, y2);
	else return min(queryMin(rt << 1, x1, mid, y1, y2), queryMin(rt << 1 | 1, mid + 1, x2, y1, y2));
}

int queryMax(int rt, int x1, int x2, int y1, int y2) {
	if (nodex[rt].l == x1 && nodex[rt].r == x2)
		return nodex[rt].queryMax(1, y1, y2);
	int mid = (nodex[rt].l + nodex[rt].r) >> 1;
	if (x2 <= mid)return queryMax(rt << 1, x1, x2, y1, y2);
	else if (x1 > mid)return queryMax(rt << 1 | 1, x1, x2, y1, y2);
	else return max(queryMax(rt << 1, x1, mid, y1, y2), queryMax(rt << 1 | 1, mid + 1, x2, y1, y2));
}