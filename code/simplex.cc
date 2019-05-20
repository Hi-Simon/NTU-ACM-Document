// 单纯形解线性规划 by zimpha
// 给出m个这样的约束条件：sum(A[i]*X[i])<=B
// 求出X的解，在满足X[i]>=0的情况下，sum(C[i]*X[i])达到最大
#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long double db;
const int N=25;
db a[N][N], eps=1e-9;
int id[N*2],n,m,t,x;
double ans[N*2];
bool pd;
db abs(db x) {return x<0?-x:x;}
void pivot(int l,int e) {
	swap(id[n+l],id[e]);
	db t=a[l][e];a[l][e]=1;
	fo(i,0,n) a[l][i]/=t;
	fo(i,0,m) 
		if (i!=l&&abs(a[i][e])>eps) {
			db t=a[i][e];a[i][e]=0;
			fo(j,0,n) a[i][j]-=t*a[l][j];
		}
}
void prepare() {
	while (1) {
		int l=0,e=0;
		fo(i,1,m) if (a[i][0]<-eps&&(!l||(rand()&1))) l=i;
		if (!l) break;
		fo(i,1,n) if (a[l][i]<-eps&&(!e||(rand()&1))) e=i;
		if (!e) {pd=1;return;}
		pivot(l,e);
	}
}
void solve() {
	while (1) {
		int l=0,e=0;db mn=1e18;
		fo(i,1,n) if (a[0][i]>eps) {e=i;break;}
		if (!e) break;
		fo(i,1,m)
			if (a[i][e]>eps&&a[i][0]/a[i][e]<mn) {
				mn=a[i][0]/a[i][e];
				l=i;
			}
		if (!l) {pd=1;return;}
		pivot(l,e);
	}
}
int main() {
	srand(233);
	scanf("%d%d%d",&n,&m,&t);
	fo(i,1,n) scanf("%d",&x),a[0][i]=x;
	fo(i,1,m) {
		fo(j,1,n) scanf("%d",&x),a[i][j]=x;
		scanf("%d",&x);
		a[i][0]=x;
	}
	fo(i,1,n+m) id[i]=i; 
	prepare();
	if (pd) { //不存在满足所有约束的解
		printf("Infeasible\n");
		return 0;
	}
	pd=0;
	solve();
	if (pd) { //对于任意的 M，都存在一组解使得目标函数的值大于 M
		printf("Unbounded\n");
		return 0;
	}
	printf("%.15lf\n",-(double)a[0][0]);
	if (t) {
		fo(i,1,m) ans[id[i+n]]=a[i][0];
		fo(i,1,n) printf("%.15lf ",ans[i]);
	}
}