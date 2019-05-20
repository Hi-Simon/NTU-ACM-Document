#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
const double eps = 1e-8;
struct Point{
	double x,y;
	Point(double xx=0.0,double yy=0.0) :x(xx) ,y(yy) {}
	Point operator - (const Point &b) const {
		return Point(x-b.x,y-b.y) ;
	}
	Point operator +(const Point &b) const {
		return Point(x+b.x,y+b.y) ;
	}
	Point operator /(const double &b) const {
		return Point(x/b,y/b) ;
	}
	Point operator *(const double &b) const {
		return Point(x*b,y*b) ;
	}
	double operator ^(const Point &b) const {
		return x*b.y-y*b.x;
	}
};
typedef Point myvec;
double cross(myvec a,myvec b) {
	return a^b;
}
struct Line{
	Point p;
	myvec v;
	double ang;
	Line() {}
	Line( Point pp,myvec vv) :p(pp) ,v(vv) {}
	bool operator < (const  Line &l) const {
		return ang < l.ang;
	}
 
};
//点p在有向直线L的左边（线上不算）
bool on_left( Line l,Point p) {
	return cross(l.v,p-l.p) >0;
}
//直线交点 假设交点唯一存在
Point get_inter_section(Line a,Line b) {
	myvec u = a.p - b. p;
	double t = cross(b.v,u) /cross(a.v,b.v) ;
	return a.p+a.v*t;
 
}
int half_plane_inter_section(Line *L,int n,Point *poly) {
	sort(L,L+n) ;//级角排序
	int fir,lst;//双向队列的第一个元素和最后一个元素的下标
	Point *p = new Point[n];//p[i] 为q[i]和q[i+1]的交点
	Line *q = new Line[n];//双端队列
	q[ fir = lst = 0 ] = L[0];//双端队列初始化为只有一个半平面的L[0]
	for( int i =1; i <n ; ++i) 
	{
		while( fir < lst && !on_left(L[i],p[lst-1])  ) 
			lst--;
		while( fir<lst && !on_left(L[i],p[fir])  ) 
			fir++;
		q[++lst] = L[i];
		if( fabs( cross(q[lst].v,q[lst-1].v)  )  < eps ) { //两向量平行且同向 取内侧一个
			lst--;
			if( on_left(q[lst],L[i].p)  ) 
				q[lst] = L[i];
		}
		if( fir < lst ) 
			p[lst-1] = get_inter_section(q[lst-1],q[lst]) ;
	}
	while( fir< lst && !on_left(q[fir],p[lst-1]) )
		lst--;//删除无用的平面
	if(lst - fir <=1 ) 
		return 0;//空集
	p[lst] = get_inter_section(q[lst],q[fir]) ;//计算首尾两个半平面的交点
	//从 deque 复制到输出中
	int m = 0 ;
	 for( int i = fir;i<=lst;++i) 
		poly[m++] = p[i];
	 return m;
}

