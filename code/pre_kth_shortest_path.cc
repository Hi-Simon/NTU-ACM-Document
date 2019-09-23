/*
 * Author: Simon 
 * 功能: 前k短路，dfs+倍增+Dijkstar+二分
 * 复杂度: O(log(Maxval)·k·log(n))
 */
#include<bits/stdc++.h>
using namespace std;
typedef int Int;
#define int long long
#define maxn 10005
#define maxm 50005
#define maxc 1005
#define maxk 10005
#define maxv maxn*1LL*maxc*maxk
#define INF maxv
namespace Dijkstra{
    struct node{
        int v,w,next;
        node(){}
        node(int v,int w,int next=-1):v(v),w(w),next(next){}
        bool operator <(const node&a)const{
            return w>a.w;
        }
    }g[maxm];
    int head[maxn],cnt=0,dis[maxn];
    bool vis[maxn];
    void init(){
        memset(head,-1,sizeof(head));cnt=0;
    }
    void addedge(int u,int v,int w){
        g[cnt]=node(v,w,head[u]);
        head[u]=cnt++;
    }
    void run(int r){
        memset(dis,INF,sizeof(dis));dis[r]=0;
        memset(vis,0,sizeof(vis));
        priority_queue<node>q;q.push({r,0});
        while(!q.empty()){
            node now=q.top();q.pop();
            int u=now.v;
            if(vis[u]) continue;vis[u]=1;
            for(int i=head[u];~i;i=g[i].next){
                int &v=g[i].v,&w=g[i].w;
                if(!vis[v]&&dis[u]+w<dis[v]){
                    dis[v]=dis[u]+w;
                    q.push({v,dis[v]});
                }
            }
        }
    }
}
namespace kth{
    int mid,num=0,ans[maxn];
    /*
     * 比较函数是为了把每个点的所有连出去的边按照 v+dis[y] 由小到大排序 
     * 其中 v 是该编的权重，dis[y] 是与 x 相邻的点到终点的最短路径。
     * 排完序后有两个好处：
     * 1. 排序后每个点连出去的第一条边就当作最短路径上的边。
     * 2. 依序枚举相邻边时，当确定一条边若走上去后到达终点的距离会超过 V，
     *    那之后的边也不必再枚举了
     */
    bool cmp(pair<int,int> a,pair<int,int> b){
        return a.second+Dijkstra::dis[a.first]<b.second+Dijkstra::dis[b.first];
    }
    vector<pair<int,int> >g[maxn];
    int nxt[maxn][21],/*i点的2^j祖先是nxt[i][j] */
        need[maxn][21],/*由i出发并在接下来2^j个祖先(不包含i)中选一个开始走最短路径树 的最少花费为need[i][j] */
        path_cost[maxn][21];/*从i点到其第2^j祖先的路径长度为path_cost[i][j] */
    void init(int n,int t){
        for(int i=1;i<=n;i++){
            if(g[i].size()){
                nxt[i][0] = g[i][0].first;
                path_cost[i][0] = g[i][0].second;
                int nt=(g[i][0].first!=t);
                if(g[g[i][0].first].size()>nt){ /*第一步走最短路径树上的节点，之后一步不走最短路径树上的点 */
                    int z=g[g[i][0].first][nt].first;
                    need[i][0] = Dijkstra::dis[z]+g[i][0].second+g[g[i][0].first][nt].second;
                }
                else need[i][0]=maxv;
            }
            else{
                nxt[i][0]=i;
                path_cost[i][0]=need[i][0]=maxv;
            }
        }
        for(int j=1;j<=20;j++){
            for(int i=1;i<=n;i++){
                nxt[i][j]=nxt[nxt[i][j-1]][j-1];
                path_cost[i][j]=path_cost[nxt[i][j-1]][j-1]+path_cost[i][j-1];
                need[i][j]=min(need[i][j-1],path_cost[i][j-1]+need[nxt[i][j-1]][j-1]);
            }
        }
    }
    void addedge(int u,int v,int w){
        g[u].push_back({v,w});
    }
    void dfs(int u,int t,int now_cost,int k){
    /*
     * 这循环是在枚举不在最短路径树上的边。
     * 当 x = t 时，连出去的所有边都不是最短路径树上的边，
     * 否则从第二条开始才是。
     * 其中 (x!=t) 等价于 (x!=t)?1:0
     */
        for(int i=(u!=t);i<g[u].size()&&num<k;i++){
            int &v=g[u][i].first,&w=g[u][i].second;
            if(now_cost+w+Dijkstra::dis[v]>mid) break;
            ans[++num]=now_cost+w+Dijkstra::dis[v];
            dfs(v,t,now_cost+w,k);
        }
        if(u!=t&&num<k&&now_cost+need[u][20]<=mid){/*保证了一定存在一个位置，使得从此位置开始不走最短路径树上的边，也能在mid要求的花费内到达终点 */
            for(int i=19;i>=0;i--){
                /* 若接下来 2^i 节点都不可能在花费小于mid情况下 不走最短路径树且到达终点，不如就先前进到点 nxt[i][x] */
                if(now_cost+need[u][i]>mid){
                    now_cost+=path_cost[u][i];
                    u=nxt[u][i];
                } 
            }
            dfs(g[u][0].first, t, now_cost + g[u][0].second, k);
        }
    }
    int solve(int s,int t,int k){
        int left=0,right=maxv;
        while(left<=right){
            mid=(left+right)>>1;
            num=0; ans[++num]=Dijkstra::dis[s];/* 先把最短路径树上起点到终点的路径算入 */
            dfs(s,t,0,k);
            if(num>=k) right=mid-1;
            else left=mid+1;
        }
        return left;
    }
}
Int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    int s,t;cin>>s>>t;
    Dijkstra::init();
    for(int i=1;i<=m;i++){
        int u,v,w;cin>>u>>v>>w;
        kth::addedge(u,v,w);
        Dijkstra::addedge(v,u,w); //建立反向边
    }
    Dijkstra::run(t);
    for(int i=1;i<=n;i++) sort(kth::g[i].begin(),kth::g[i].end(),kth::cmp); 
    kth::init(n, t);
    int res=kth::solve(s,t,k);
    /* 
     * 虽然已经知道第 k 短路径长度是 res，但得再把门槛设为 res - 1 后再搜索一次，
     * 不足 k 个的值再补上 res，否则直接用 res 当门槛去搜索的话，
     * 可能会搜出过多的长度为 low 的路径。
     */
    kth::num=0;kth::mid=res-1;
    kth::ans[++kth::num]=Dijkstra::dis[s];
    kth::dfs(s,t,0,k);
    sort(kth::ans+1,kth::ans+kth::num+1);
    while(kth::num<k) kth::ans[++kth::num]=res;
    for(int i=1;i<=kth::num;i++){
        if(kth::ans[i]>=INF) cout<<"NO"<<endl;
        else cout<<kth::ans[i]<<endl; 
    }
    cin.get(),cin.get();
    return 0;
}