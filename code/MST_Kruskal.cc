/*
 * Author: Simon
 * 复杂度: mlog(m)
 * 功能: 适用于稀疏图求MST
 */
namespace Kruskal{
    int Set[maxn], Rank[maxn],cnt=0;//并查集 rank
    struct node{
        int u,v,w;
        node(){}
        node(int u,int v,int w):u(u),v(v),w(w){}
        bool operator <(const node&a)const{
            return w<a.w;
        }
    }g[maxm];//结构体储存
    void init(int n) {
        for (int i = 0; i <= n; i++) {
            Rank[i] = 0; Set[i] = i;
        }
    }
    void addedge(int u,int v,int w){
        g[cnt++]=node(u,v,w);
    }
    int find(int x) {
        int root = x;
        while (root != Set[root]) root = Set[root];
        while (x != root) {
            int t = Set[x];
            Set[x] = root;
            x = t;
        }
        return root;
    }
    void unite(int x, int y) {
        x = find(x); y = find(y);
        if (Rank[x] < Rank[y]) {
            Set[x] = y;
        } else {
            Set[y] = x;
            if (Rank[x] == Rank[y]) Rank[x]++;
        }
    }
    //n为边的数量，m为村庄的数量
    int Run(int n, int m) {
        int num = 0, res = 0; //将边按照权值从小到大排序
        sort(g,g+cnt);
        for (int i = 0; i < n && num != m - 1; i++) {
            int u=g[i].u,v=g[i].v,w=g[i].w;
            //判断当前这条边的两个端点是否属于同一棵树
            if (find(u) != find(v)) {
                unite(u, v);
                res += w;
                num++;
            }
        }
        //如果加入边的数量小于m - 1,则表明该无向图不连通,等价于不存在最小生成树
        if (num < m - 1) res = -1;
        return res;
    }
}