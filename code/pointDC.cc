/*
 * Author: Simon
 * 复杂度: O(nlog(n))
 * 功能: 点分治求树上满足边长小于k的（u，v）的对数
 */
namespace PDC {
    struct node {
        int v, w, next;
        node() {}
        node(int v, int w, int next) : v(v), w(w), next(next) {}
    } g[maxn << 1];
    int head[maxn], cnt = 0;
    int rt /*树重心*/, son[maxn] /*不包含当前节点的所有子树的最大size*/, sz[maxn] /*当前节点为根的子树的size*/;
    int q[maxn] /*子树所有节点到根节点的距离*/, len, ans = 0;
    bool vis[maxn];
    void init() {
        memset(head, -1, sizeof(head));
        memset(vis, 0, sizeof(vis));
        ans = 0; son[0] = INF; cnt = 0;
    }
    void addedge(int u, int v, int w) {
        g[cnt] = node(v, w, head[u]);
        head[u] = cnt++;
    }
    void getrt(int u, int p, int tot) { /*获得树的重心*/
        sz[u] = 1; son[u] = 0;
        for (int i = head[u]; ~i; i = g[i].next) {
            int v = g[i].v;
            if (v == p || vis[v]) continue;
            getrt(v, u, tot);
            sz[u] += sz[v];
            son[u] = max(son[u], sz[v]);
        }
        son[u] = max(son[u], tot - sz[u]);
        if (son[u] < son[rt]) rt = u;
    }
    void getdis(int u, int p, int pw) { /*求出以u为根节点的所有子节点到fa[u]的距离*/
        q[++len] = pw; sz[u] = 1;
        for (int i = head[u]; ~i; i = g[i].next) {
            int v = g[i].v, w = g[i].w;
            if (v == p || vis[v]) continue;
            getdis(v, u, pw + w);
            sz[u] += sz[v];
        }
    }
    int solve(int u, int w) { /*根据具体题目变化*/
        len = 0; getdis(u, -1, w);
        sort(q + 1, q + r + 1); /*按到根节点的距离排序*/

        int ans = 0, l = 1, r = len;
        while (l < r) {
            if (q[l] + q[r] <= k) ans += r - l, l++; /*若q[l]+q[r]<=k，则q[l]+q[l+1],q[l]+q[l+2],...,q[l]+q[r]都满足<=k*/
            else r--;
        }
        /* 求有多少条长度为k的路径
        int l = 1, r = 1, ans = 0;
        for (int i = 1; i <= len; i++) {
            l = lower_bound(q + i + 1, q + len + 1, k - q[i]) - q;
            r = upper_bound(q + i + 1, q + len + 1, k - q[i]) - q;
            ans += r - l; //求得到根节点长度为k-q[i]的路径个数
        }
        */
        return ans;
    }
    void dfs(int u) {
        vis[u] = 1; ans += solve(u, 0); /*先算上以u为根的子树的贡献*/
        for (int i = head[u]; ~i; i = g[i].next) {
            int v = g[i].v, w = g[i].w;
            if (vis[v]) continue;
            ans -= solve(v, w); /*减去以u~v这条边为重边而多计算的部分*/
            rt = 0; getrt(v, -1, sz[v]); /*求以v的子树的重心*/
            dfs(rt);
        }
    }
    void Run(int u, int n) {
        getrt(1, -1, n);
        dfs(rt);
    }
}