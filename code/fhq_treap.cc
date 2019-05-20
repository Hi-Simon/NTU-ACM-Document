#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
const int MAXN=100001;
static void read(int &n) {
	char c='+';int x=0;bool flag=0;
	while(c<'0'||c>'9'){c=getchar();if(c=='-')flag=1;}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c-48);c=getchar();}
	flag==1?n=-x:n=x;
}
int ch[MAXN][3];// 0左孩子 1右孩子
int val[MAXN];// 每一个点的权值
int pri[MAXN];// 随机生成的附件权值
int siz[MAXN];// 以i为节点的树的节点数量
int sz;// 总结点的数量 
void update(int x) {
	siz[x]=1+siz[ch[x][0]]+siz[ch[x][1]];
} 
int new_node(int v) {
	siz[++sz]=1;// 新开辟一个节点
	val[sz]=v;
	pri[sz]=rand(); 
	return sz;
}
int merge(int x,int y) {// 合并 
	if(!x||!y)    return x+y;// x和y中必定有一个是0
	if(pri[x]<pri[y])// 把x加到左边的树上 
	{
		ch[x][1]=merge(ch[x][1],y);// 不懂的看GIF图 
		update(x);
		return x;
	} 
	else
	{
		ch[y][0]=merge(x,ch[y][0]);
		update(y);
		return y;
	}
}
void split(int now,int k,int &x,int &y) {
	if(!now) x=y=0;// 到达叶子节点
	else {
		if(val[now]<=k)// 分离右子树    
			x=now,split(ch[now][1],k,ch[now][1],y);
		else 
			y=now,split(ch[now][0],k,x,ch[now][0]);
		update(now);
	} 
}
int kth(int now,int k) {// 查询排名 
	while(1) {
		if(k<=siz[ch[now][0]])
			now=ch[now][0];// 在左子树中，且数量小于左子树的大小，迭代寻找
		else if(k==siz[ch[now][0]]+1)
			return now;// 找到了
		else 
			k-=siz[ch[now][0]]+1,now=ch[now][1];// 去右子树找 
	}
}
int main() {
	srand((unsigned)time(NULL));
	int n;
	read(n);
	int root=0,x,y,z;
	for(int i=1;i<=n;i++) {
		int how,a;
		read(how);read(a);
		if(how==1) {// 插入 
			split(root,a,x,y);
			root=merge(merge(x,new_node(a)),y);
		}
		else if(how==2) {//删除x 
		{
			split(root,a,x,z);
			split(x,a-1,x,y);
			y=merge(ch[y][0],ch[y][1]);
			root=merge(merge(x,y),z);
		}
		else if(how==3) {//查询x的排名 
			split(root,a-1,x,y);
			printf("%d\n",siz[x]+1);
			root=merge(x,y);
		}
		else if(how==4) {// 查询排名为x的数 
			printf("%d\n",val[kth(root,a)]);
		}
		else if(how==5) {// 求x的前驱 
			split(root,a-1,x,y);
			printf("%d\n",val[kth(x,siz[x])]);
			root=merge(x,y);
		}
		else if(how==6) {// 求x的后继 
			split(root,a,x,y);
			printf("%d\n",val[kth(y,1)]);
			root=merge(x,y);
		}
	}
	return 0;
}