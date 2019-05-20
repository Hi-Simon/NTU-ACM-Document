// 扫描线 求 矩形最大点覆盖
struct Line {
	ll x, y1, y2, k;	// k 为矩形权值
	bool operator < (const Line nod) const {
		return x < nod.x || (x == nod.x && k < nod.k);
	}
}line[maxn];
struct segTree {
	ll ma, l, r, lazy;
}tree[maxn << 2];
ll yy[maxn];
int cnt, ycnt;
void pushup(int rt) {
	tree[rt].ma = max(tree[rt << 1].ma, tree[rt << 1 | 1].ma) + tree[rt].lazy;
}
void build(int l, int r, int rt) {
	tree[rt].ma = tree[rt].lazy = 0;
	tree[rt].l = yy[l], tree[rt].r = yy[r];
	if (r - l == 1) return;
	int mid = (l + r) >> 1;
	build(l, mid, rt << 1);
	build(mid, r, rt << 1 | 1);
	pushup(rt);
}
void update(ll L, ll R, ll w, int rt) {
	if (tree[rt].l >= L && tree[rt].r <= R) {
		tree[rt].lazy += w;
		tree[rt].ma += w;
		return;
	}
	if (L < tree[rt << 1].r)
		update(L, min(R, tree[rt << 1].r), w, rt << 1);
	if (R > tree[rt << 1 | 1].l)
		update(max(tree[rt << 1 | 1].l, L), R, w, rt << 1 | 1);
	pushup(rt);
}
int main()
{
	ll n, W, H, x, y, w, ma;
	while (~scanf("%lld%lld%lld", &n, &W, &H)) {
		cnt = 0; ycnt = 1; ma = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%lld%lld%lld", &x, &y, &w);
			line[cnt].x = x; line[cnt].y1 = y; line[cnt].y2 = y + H;
			line[cnt++].k = w;
			line[cnt].x = x + W; line[cnt].y1 = y; line[cnt].y2 = y + H;
			line[cnt++].k = -w;
			yy[ycnt++] = y;
			yy[ycnt++] = y + H;
		}
		sort(yy + 1, yy + ycnt);
		ycnt = unique(yy + 1, yy + ycnt) - (yy + 1);
		sort(line, line + cnt);
		build(1, ycnt, 1);
		for (int i = 0; i < cnt; i++) {
			update(line[i].y1, line[i].y2, line[i].k, 1);
			if (line[i].k > 0) ma = max(ma, tree[1].ma);
		}
		printf("%lld\n", ma);
	}
	return 0;
}