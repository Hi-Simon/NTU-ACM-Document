//二维带权最大上升子序列
//written by Simon

#include<bits/stdc++.h>
using namespace std;
typedef int Int;
#define int long long
#define INF 0x3f3f3f3f
#define maxn 100005
int bin[maxn];//用于二分
struct cmp_key{//map排序辅助结构体,第一维升序，第二维降序
	bool operator ()(const pair<int,int>&a,const pair<int,int>&b){
		if(a.first==b.first){
			return a.second>b.second;
		}
		else return a.first<b.first;
	}
};
map<pair<int,int>,int,cmp_key>p;
int binary_search(int v,int n){
	int left=0,right=n,mid;
	while(left<=right){
		mid=(left+right)>>1;
		if(bin[mid]<v){
			left=mid+1;
		}
		else right=mid-1;
	}
	return left;
}
int tree[maxn];
int lowbit(int x){
	return (x&(-x));
}
void update(int x,int v,int len){
	for(int i=x;i<=len;i+=lowbit(i)){
		tree[i]=max(tree[i],v);
	}
}
int get(int x,int len){
	int sum=0;
	for(int i=x;i>=1;i-=lowbit(i)){
		sum=max(sum,tree[i]);
	}
	return sum;
}
Int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
	int n; 
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		int x,y,v;
		scanf("%lld%lld%lld",&x,&y,&v);
		p[make_pair(x,y)]+=v;//去重（关键）
		bin[i]=y;
	}
	sort(bin+1,bin+n+1);
	auto len=unique(bin+1,bin+n+1)-(bin+1);//去重
	for(auto v:p){
		int x=binary_search(v.first.second,len);
		int val=get(x-1,len);
		update(x,val+v.second,len);
	}
	printf("%lld\n",get(len,len));
    cin.get(),cin.get();
    return 0;
}