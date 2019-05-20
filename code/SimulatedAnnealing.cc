//模拟退火
//平面上找一个点 使得 sigma(1..N)dist(a, i)*Wi 最小

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>

#define INF (1e17)
#define EPS (1e-3)
#define PI  (acos(-1.0))
#define FIRE(x) (x *= 0.99)
using namespace std;
const int MAXN = 10000 + 10;
int N;
double total = INF;
struct Point {
	double x, y, w;
	Point (double _x, double _y) : x(_x), y(_y) {}
	Point (void) {}
	void Read(void) {
		scanf("%lf%lf%lf", &x, &y, &w);
	}
	void operator += (Point t) {
		x += t.x; y += t.y;
	}
	void operator /= (int N) {
		x /= N, y /= N;
	}
};
Point now, ans, point[MAXN];
inline double Dist(Point a, Point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) +
				 (a.y - b.y) * (a.y - b.y));
}
inline double Statistic(Point p) {
	double res = 0.0;
	for (int i = 0; i < N; i++) res += Dist(p, point[i]) * point[i].w;
	if (res < total) total = res, ans = p;
	return res;
}
inline double Rand(void) {
	return (rand() % 1000 + 1) / 1000.0;
}
int main(void) {
	srand(10086);
	scanf("%d", &N);
	register int i;
	for (i = 0; i < N; i++) point[i].Read(), now += point[i];
	now /= N;
	double T = 100000.0, alpha, sub;
	while (T > EPS) {
		alpha = 2.0 * PI * Rand();
		Point tmp(now.x + T * cos(alpha), now.y + T * sin(alpha));
		sub = Statistic(now) - Statistic(tmp);
		if(sub >= 0 || exp(sub / T) >= Rand()) now = tmp;
		FIRE(T);
	}
	T = 0.001;
	for (i = 1; i <= 1000; ++i) {
		alpha = 2.0 * PI * Rand();
		Point tmp(ans.x + T * cos(alpha) * Rand(), ans.y + T * sin(alpha) * Rand());
		Statistic(tmp);
	}
	printf("%.3lf %.3lf\n", ans.x, ans.y);
	return 0;
}