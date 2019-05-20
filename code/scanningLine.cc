// 矩形面积并（交） 求并FLAG=0，求交FLAG=1
struct Line {
	double l, r, h;
	int d;
	Line() {}
	Line(double l, double r, double h, int d) : l(l), r(r), h(h), d(d) {}
	bool operator < (const Line L) const {
		return h < L.h;
	}
}line[maxn << 1];

int FLAG;	// 求矩形面积并 FLAG = 0，求矩形面积交 FLAG = 1
int Cover[maxn << 3];
double A[maxn << 1];
double Sum[maxn << 3];
double X1[maxn << 1], X2[maxn << 1], Y1[maxn << 1], Y2[maxn << 1];

void pushdown(int rt, int l, int r) {
	int mid = (l + r) >> 1;
	if (Cover[rt] != -1) {
		Cover[rt << 1] = Cover[rt << 1 | 1] = Cover[rt];
		Sum[rt << 1] = (Cover[rt] > FLAG ? (A[mid + 1] - A[l]) : 0);
		Sum[rt << 1 | 1] = (Cover[rt] > FLAG ? (A[r + 1] - A[mid + 1]) : 0);
	}
}

void pushup(int rt, int l, int r) {
	if (Cover[rt << 1] == -1 || Cover[rt << 1 | 1] == -1) Cover[rt] = -1;
	else if (Cover[rt << 1] != Cover[rt << 1 | 1]) Cover[rt] = -1;
	else Cover[rt] = Cover[rt << 1];
	Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1];
}

void build(int l, int r, int rt) {
	if (l == r) {
		Cover[rt] = 0;
		Sum[rt] = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, rt << 1);
	build(mid + 1, r, rt << 1 | 1);
	pushup(rt, l, r);
}

void update(int L, int R, int v, int l, int r, int rt) {
	if (L <= l && r <= R) {
		if (Cover[rt] != -1) {
			Cover[rt] += v;
			Sum[rt] = (Cover[rt] > FLAG ? (A[r + 1] - A[l]) : 0);
			return;
		}
	}
	pushdown(rt, l, r);
	int mid = (l + r) >> 1;
	if (L <= mid) update(L, R, v, l, mid, rt << 1);
	if (mid < R) update(L, R, v, mid + 1, r, rt << 1 | 1);
	pushup(rt, l, r);
}

int find(double key, int n, double d[]) {
	int l = 1, r = n;
	while (r >= l) {
		int mid = (r + l) >> 1;
		if (d[mid] == key) return mid;
		else if (d[mid] > key) r = mid - 1;
		else l = mid + 1;
	}
	return -1;
}

int init(int n) {
	int N = 0;
	for (int i = 1; i <= n; i++) {
		A[++N] = X1[i];
		line[N] = Line(X1[i], X2[i], Y1[i], 1);
		A[++N] = X2[i];
		line[N] = Line(X1[i], X2[i], Y2[i], -1);
	}
	sort(A + 1, A + N + 1);
	sort(line + 1, line + N + 1);
	int k = 1;
	for (int i = 2; i <= N; i++)
		if (A[i] != A[i - 1])
			A[++k] = A[i];
	build(1, k - 1, 1);
	return k;
}

double query(int n, int k) {
	double ret = 0;
	for (int i = 1; i < n; i++) {
		int l = find(line[i].l, k, A);
		int r = find(line[i].r, k, A) - 1;
		if (l <= r) update(l, r, line[i].d, 1, k - 1, 1);
		ret += Sum[1] * (line[i + 1].h - line[i].h);
	}
	return ret;
}
/*
int main()
{
	int n, T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%lf%lf%lf%lf", &X1[i], &Y1[i], &X2[i], &Y2[i]);
		int k = init(n);
		double ans = query(n << 1, k);
		printf("%.2lf\n", ans);
	}
}
*/

//==========================================================================================

// 矩形周长并
int Sum[maxn << 3], cnt[maxn << 3], vNum[maxn << 3];
bool lbd[maxn << 3], rbd[maxn << 3];
double X1[maxn << 1], X2[maxn << 1], Y1[maxn << 1], Y2[maxn << 1];
double A[maxn << 1];

struct Line {
	double l, r, h;
	int label;
	Line() {}
	Line(double l, double r, double h, int label) :l(l), r(r), h(h), label(label) {}
	bool operator < (const Line L) const {
		return h < L.h;
	}
}line[maxn << 1];

void pushup(int l, int r, int rt) {
	if (cnt[rt]) {
		lbd[rt] = rbd[rt] = true;
		Sum[rt] = A[r + 1] - A[l];
		vNum[rt] = 2;
	}
	else if (l == r) Sum[rt] = vNum[rt] = lbd[rt] = rbd[rt] = 0;
	else {
		lbd[rt] = lbd[rt << 1];
		rbd[rt] = rbd[rt << 1 | 1];
		Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1];
		vNum[rt] = vNum[rt << 1] + vNum[rt << 1 | 1];
		if (rbd[rt << 1] && lbd[rt << 1 | 1]) vNum[rt] -= 2;
	}
}

void update(int L, int R, int v, int l, int r, int rt) {
	if (L <= l && r <= R) {
		cnt[rt] += v;
		pushup(l, r, rt);
		return;
	}
	int mid = (l + r) >> 1;
	if (L <= mid) update(L, R, v, l, mid, rt << 1);
	if (R > mid) update(L, R, v, mid + 1, r, rt << 1 | 1);
	pushup(l, r, rt);
}

int find(double key, int n, double d[]) {
	int l = 1, r = n;
	while (r >= l) {
		int mid = (r + l) >> 1;
		if (d[mid] == key) return mid;
		else if (d[mid] > key) r = mid - 1;
		else l = mid + 1;
	}
	return -1;
}

int init(int n) {
	for (int i = 1; i <= n; i++) {
		A[i] = X1[i]; A[i + n] = X2[i];
		line[i].l = X1[i]; line[i].r = X2[i];
		line[i].h = Y1[i]; line[i].label = 1;
		line[i + n].l = X1[i]; line[i + n].r = X2[i];
		line[i + n].h = Y2[i]; line[i + n].label = -1;
	}
	n <<= 1;
	int k = 1;
	sort(A + 1, A + n + 1);
	sort(line + 1, line + n + 1);
	for (int i = 2; i <= n; i++)
		if (A[i] != A[i - 1])
			A[++k] = A[i];
	return k;
}

double query(int n, int k) {
	double ret = 0, lst = 0;
	for (int i = 1; i <= n; i++) {
		if (line[i].l < line[i].r) {
			int l = find(line[i].l, k, A);
			int r = find(line[i].r, k, A);
			update(l, r - 1, line[i].label, 1, k - 1, 1);
		}
		ret += vNum[1] * (line[i + 1].h - line[i].h);
		ret += abs(Sum[1] - lst);
		lst = Sum[1];
	}
	return ret;
}
/*
int main()
{
	int n;
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++)
			scanf("%lf%lf%lf%lf", &X1[i], &Y1[i], &X2[i], &Y2[i]);
		int k = init(n);
		double ans = query(n << 1, k);
		printf("%lf\n", ans);
	}
	return 0;
}
*/