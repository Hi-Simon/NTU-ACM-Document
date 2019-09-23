/*
 * Author: Simon
 * 功能: 全局k短路
 * 复杂度: mlog(m)+klog(k)
 * 多次查询，k为最大的k
 */
#include<bits/stdc++.h>
using namespace std;
typedef int Int;
#define int long long
#define INF 0x3f3f3f3f
#define maxn 50005
struct node{
    int u,v,w,rank/*从u出发的，第rank短的边*/;
    node(){}
    node(int u,int v,int w,int rank):u(u),v(v),w(w),rank(rank){}
    bool operator <(const node&a)const{
        return w>a.w;
    }
};
int a[maxn];
struct pi{
    int u,v,w;
    pi(){}
    pi(int u,int v,int w):u(u),v(v),w(w){}
    bool operator <(const pi&a) const{
        return w<a.w;
    }
};
vector<pi>g[maxn];
Int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,m,qq;cin>>n>>m>>qq;/*n个点，m条边，qq次查询*/
        priority_queue<node>q;
        for(int i=1;i<=m;i++){
            int u,v,w;
            cin>>u>>v>>w;
            g[u].push_back({u,v,w});
        }
        for(int i=1;i<=n;i++) sort(g[i].begin(),g[i].end()); //按边权从小到大排序
        for(int i=1;i<=n;i++) if(g[i].size()) q.push({g[i][0].u,g[i][0].v,g[i][0].w,0}); //初始将所有点的最短出边入队列
        int Max=0; for(int i=1;i<=qq;i++) cin>>a[i],Max=max(Max,a[i]); //最大要算到第Max小的路径
        vector<int>ans;
        for(int i=1;i<=Max;i++){
            node now=q.top();q.pop();
            ans.push_back(now.w); //第i次出队列的边权长度，就是第i小的路径长度
            if(g[now.v].size()){ //1、从v点出发的最短边
                int u=now.v,v=g[now.v][0].v,w=g[now.v][0].w;
                q.push({u,v,w+now.w,0});
            }
            if(g[now.u].size()>now.rank+1){//2、由u-v转为u-v'
                int u=now.u,v=g[now.u][now.rank+1].v,w=g[now.u][now.rank+1].w;
                q.push({u,v,now.w+w-g[now.u][now.rank].w,now.rank+1});
            }
        }
        for(int i=1;i<=qq;i++) cout<<ans[a[i]-1]<<endl;
        for(int i=0;i<=n;i++) g[i].clear();
    }
    return 0;
}