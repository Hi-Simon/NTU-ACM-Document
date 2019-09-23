/*
 * Author: Simon
 * 功能: 第k小带权匹配(枚举点)
 * 复杂度: O(k·m·log(1000·n))
 */
#include<bits/stdc++.h>
using namespace std;
typedef int Int;
#define int long long
#define INF 0x3f3f3f3f
#define maxn 25
#define maxm 1005
struct node{
    int v,w,next;
    node(){}
    node(int v,int w,int next):v(v),w(w),next(next){}
}g[maxm];
int num=0/*所有匹配中权值和小于期望值mid的匹配数 */,mid/*第k小匹配的期望值 */,head[maxn],cnt=0;
void init(){
    memset(head,-1,sizeof(head));
    cnt=0;
}
void addedge(int u,int v,int w){
    g[cnt]=node(v,w,head[u]);
    head[u]=cnt++;
}
bool vis[maxn];
void dfs(int u,int val,int n,int k){
    if(val>mid) return ;
    if(u>n){
        if(val<=mid) num++; 
        return ;
    }
    dfs(u+1,val,n,k); /*可能不选 */
    for(int i=head[u];~i&&num<k/*关键剪枝 */;i=g[i].next){
        int &v=g[i].v,&w=g[i].w;
        if(!vis[v]&&val+w<=mid){ /*v节点未匹配，并且匹配后总权值小于等于 期望值mid */
            vis[v]=1;
            dfs(u+1,val+w,n,k);
            vis[v]=0;
        }
    }
}
Int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    int n,m,k;cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v,w;cin>>u>>v>>w;
        addedge(u,v,w);
    }
    int left=0,right=1000*n;/*每条边的最大权值为1000，最多有n/2个点 */
    while(left<=right){
        mid=(left+right)>>1; /*假设一个第k小匹配和的期望 */
        num=0; dfs(1,0,n,k); /*暴力枚举判断满足小于等于mid的匹配有没有k个 */
        if(num>=k) right=mid-1;/*若有，则减少期望值 */
        else left=mid+1; /*否则增加期望值 */
    }
    cout<<left<<endl;
    cin.get(),cin.get();
    return 0;
}
/*
 * Author: Simon
 * 功能: 第k小带权匹配(枚举边)
 * 复杂度: O(k·log(1000·n))
 */
#include<bits/stdc++.h>
using namespace std;
typedef int Int;
#define int long long
#define INF 0x3f3f3f3f
#define maxn 25
#define maxm 1005
struct node{
    int b,w;
    bool operator <(const node&a)const{
        if(w==a.w) return b<a.b;
        return w<a.w;
    }
}g[maxm];
int mid,num=0;
void dfs(int i,int m,int k,int val,int mask){
    if(i>m) return ;
    if(num>=k) return ; /*剪枝 */
    if(val+g[i].w>mid) return ; /*因为排过序，所以以后的边肯定大于g[i].w */
    if(!(mask&g[i].b)){ /*当前此条边的u,v节点未被选过 */
        num++; /*因为不选的在选的后面，所以这里可以直接计数 */
        dfs(i+1,m,k,val+g[i].w,mask|g[i].b);
    }
    dfs(i+1,m,k,val,mask); /*不选此条边,因为边权从小到大排好序，所以不选放在选的后面 */
}
Int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v,w;cin>>u>>v>>w;
        g[i].b=(1LL<<(u+n))|(1LL<<v); /*将u~v这条边hash处理 */
        g[i].w=w;
    }
    sort(g+1,g+m+1); /*从小到大排序 */
    int left=0,right=1000*n;
    while(left<=right){
        mid=(left+right)>>1;
        num=1;/*全不选的方案 */dfs(1,m,k,0,0);
        if(num>=k) right=mid-1;
        else left=mid+1;
    }
    cout<<left<<endl;
    cin.get(),cin.get();
    return 0;
}