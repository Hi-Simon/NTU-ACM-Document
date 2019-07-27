int N;
int c[maxn][maxn];

inline int lowbit(int t) {
	return t&(-t);
}

void update(int x, int y, int v) {
	for (int i=x; i<=N; i+=lowbit(i)) {
		for (int j=y; j<=N; j+=lowbit(j)) {
			c[i][j]+=v;
		}
	}
}

int query(int x, int y) {
	int s = 0;
	for (int i=x; i>0; i-=lowbit(i)) {
		for (int j=y; j>0; j-=lowbit(j)) {
			s += c[i][j];
		}
	}
	return s;
}

int sum(int x, int y, int xx, int yy) {
	x--, y--;
	return query(xx, yy) - query(xx, y) - query(x, yy) + query(x, y);
}
/*
 * Author: Simon
 * 功能: 二维区间修改，区间查询
 * 若要修改的矩形区间为[x1,y1]~[x2,y2]，则更新的点为
 * update(x1,y1,val);update(x2+1,y2+1,val);update(x1,y2+1,-val);update(x2+1,y1,-val);
 * 若要查询的举行区间为[x1,y1]~[x2,y2]，则查询的值为
 * query(x2,y2)-query(x1-1,y2)-query(x2,y1-1)+query(x1-1,y1-1)
 */
int tree1[maxn][maxn],tree2[maxn][maxn],tree3[maxn][maxn],tree4[maxn][maxn];
inline int lowbit(int x){
    return x&(-x);
}
inline void update(int x,int y,int val){
    for(int i=x;i<maxn;i+=lowbit(i)){
        for(int j=y;j<maxn;j+=lowbit(j)){
            tree1[i][j]+=val;tree2[i][j]+=(x-1)*val;
            tree3[i][j]+=(y-1)*val;tree4[i][j]+=(x-1)*(y-1)*val;
        }
    }
}
inline int query(int x,int y){
    int ans=0;
    for(int i=x;i>0;i-=lowbit(i)){
        for(int j=y;j>0;j-=lowbit(j)){
            ans+=(x*y)*tree1[i][j]-y*tree2[i][j]-x*tree3[i][j]+tree4[i][j];
        }
    }
    return ans;
}
int a[maxn][maxn];
int main(){
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
            update(i,j,a[i][j]-a[i-1][j]-a[i][j-1]+a[i-1][j-1]);
        }
    }
    update(2,3,10);update(7,6,10);update(2,6,-10);update(7,3,-10); 
    /*将矩形区间[2,3]-[6,5]所有的值增加10 */
    printf("%d\n",query(4,5)+query(2,1)-query(2,5)-query(4,2)); 
    /*查询矩形区间[3,2]-[4,5]的和 */
}