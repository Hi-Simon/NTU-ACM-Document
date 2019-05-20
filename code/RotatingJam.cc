struct Point {
	int x, y;
	Point(int _x = 0, int _y = 0) {
		x = _x;
		y = _y;
	}
	Point operator - (const Point &b)const {
		return Point(x - b.x, y - b.y);
	}
	int operator ^(const Point &b)const {
		return x * b.y - y * b.x;
	}
	int operator *(const Point &b)const {
		return x * b.x + y * b.y;
	}
	void input() {
		scanf("%d%d", &x, &y);
		return ;
	}
};

//  距离的平方
int dist2(Point a, Point b) {
	return (a - b) * (a - b);
}

//  二维凸包,int
const int MAXN = 50010;
Point list[MAXN];
int Stack[MAXN], top;
bool _cmp(Point p1, Point p2) {
	int tmp = (p1 - list[0]) ^ (p2 - list[0]);
	if (tmp > 0) {
		return true;
	}
	else if (tmp == 0 && dist2(p1, list[0]) <= dist2(p2, list[0])) {
		return true;
	} else {
		return false;
	}
}

void Graham(int n) {
	Point p0;
	int k = 0;
	p0 = list[0];
	for (int i = 1; i < n; i++) {
		if (p0.y > list[i].y || (p0.y == list[i].y && p0.x > list[i].x)) {
			p0 = list[i];
			k = i;
		}
	}
	swap(list[k], list[0]);
	sort(list + 1, list + n, _cmp);
	if (n == 1) {
		top = 1;
		Stack[0] = 0;
		return ;
	}
	if (n == 2) {
		top = 2;
		Stack[0] = 0;
		Stack[1] = 1;
		return ;
	}
	Stack[0] = 0;
	Stack[1] = 1;
	top = 2;
	for (int i = 2; i < n; i++) {
		while (top > 1 && ((list[Stack[top - 1]] - list[Stack[top - 2]]) ^ (list[i] - list[Stack[top - 2]])) <= 0) {
			top--;
		}
		Stack[top++] = i;
	}
	return ;
}

//  旋转卡壳,求两点间距离平方的最大值
int rotating_calipers(Point p[],int n) {
	int ans = 0;
	Point v;
	int cur = 1;
	for (int i = 0; i < n; i++) {
		v = p[i] - p[(i + 1) % n];
		while ((v ^ (p[(cur + 1) % n] - p[cur])) < 0) {
			cur = (cur + 1) % n;
		}
		ans = max(ans, max(dist2(p[i], p[cur]), dist2(p[(i + 1) % n], p[(cur + 1) % n])));
	}
	return ans;
}

Point p[MAXN];

int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) {
			list[i].input();
		}
		Graham(n);
		for (int i = 0; i < top; i++) {
			p[i] = list[Stack[i]];
		}
		printf("%d\n", rotating_calipers(p, top));
	}
	return 0;
}