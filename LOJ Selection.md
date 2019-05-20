[TOC]



## 图论

### 最短路

```c++
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <utility>

using namespace std;

namespace Input
{
	const int BUF = 65536;
	char buf[BUF + 1];
	char *head = buf, *tail = buf;

	inline char inputchar()
	{
		if (head == tail)
			*(tail = (head = buf) + fread(buf, 1, BUF, stdin)) = 0;
		return *head++;
	}

	inline void inputnum(int &ret)
	{
		char ch = inputchar();
		while (ch < '0' || ch > '9')
			ch = inputchar();
		for (ret = 0; ch >= '0' && ch <= '9'; ch = inputchar())
			ret = ret * 10 + ch - '0';
	}
}
using Input::inputnum;

typedef long long s64;

const int MAXN = 2505;
const int MAXM = 6205;
const s64 INF = 1ll << 62;

struct Edge
{
	int to, next, w;
	Edge() {}
}e[MAXM << 1];
int head[MAXN], te = 1;

inline void insertE(int u, int v, int w)
{
	e[++te].to = v;
	e[te].next = head[u];
	e[te].w = w;
	head[u] = te;
}

int n, m, s, t, u, v, w;

s64 dijkstra(int s, int t)
{
	static priority_queue<pair<s64, int> > pq;
	static s64 dis[MAXN];
	for (int i = 1; i <= n; i++)
		dis[i] = INF;
	dis[s] = 0;
	pq.push(make_pair(-dis[s], s));
	while (!pq.empty())
	{
		pair<s64, int> now = pq.top();
		pq.pop();
		int u = now.second;
		if (dis[u] != -now.first)
			continue;
		for (int j = head[u]; j != 0; j = e[j].next)
		{
			int v = e[j].to;
			if (dis[v] > dis[u] + e[j].w)
			{
				dis[v] = dis[u] + e[j].w;
				pq.push(make_pair(-dis[v], v));
			}
		}
	}
	return dis[t];
}

int main()
{
	inputnum(n), inputnum(m), inputnum(s), inputnum(t);
	memset(head, 0, sizeof(head));
	for (int i = 1; i <= m; i++)
	{
		inputnum(u), inputnum(v), inputnum(w);
		insertE(u, v, w);
		insertE(v, u, w);
	}
	printf("%lld\n", dijkstra(s, t));
	return 0;
}
```



### 最小生成树

```c++
#include<cstdio>
#include<algorithm>
int n,m,fa[200010];
struct edge{int u,v,w;bool operator<(const edge&e)const{return w<e.w;}}E[500010];
int find(int i){return fa[i]==i?i:fa[i]=find(fa[i]);}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
	std::sort(E,E+m);
	for(int i=1;i<=n;i++)fa[i]=i;
	long long S=0;
	for(int i=0,fu,fv;i<m;i++)
		if((fu=find(E[i].u))!=(fv=find(E[i].v)))S+=E[i].w,fa[fu]=fv;
	printf("%lld\n",S);
}
```



### 动态图连通性（离线）

``` c++
#include"bits/stdc++.h"

using namespace std;

namespace io{
	const int L=(1<<20)+1;
	char _buf[L],*S,*T,c;
	#define gc (S==T ? T=(S=_buf)+fread(_buf,1,L,stdin), *S++ : *S++)
	void gi(int&x){
		for(c=gc;c<'0'||c>'9';c=gc); x=c&15;
		for(c=gc;c>='0'&&c<='9';c=gc) x=x*10+(c&15);
	}
	char obuf[L],*op=obuf,*end=obuf+(L-1);
	void writechar(char x){
		*op++=x;
		if(op==end)fwrite(obuf,1,L-1,stdout),op=obuf;
	}
	void cbuf(){
		fwrite(obuf,1,op-obuf,stdout),op=obuf;
	}
};
using io::gi;
using io::writechar;

#define pb push_back
#define mfy(x,y) (va[++sk]=x,*(stk[sk]=&x)=y)
const int N=1050005,M=25000005,L=500005,A=5005,D=33554435;

vector<int>E[N];
int n,m,l=1,d,lm,x,y,_O[L],u[L],tu[N],tv[N],sk,va[M],fa[A],sz[A],lst[D],au[N],av[N];
bool exi[N];

int find(int x){return fa[x]==x?x:find(fa[x]);}
void addedge(int s,int t,int ins){
	int q,p;
	while(s<=t){
		q=min(31-__builtin_clz(t-s+1), __builtin_ctz(s-1));
		if(exi[p=s+l-1>>q])E[p].pb(ins);
		s+=1<<q;
	}
}
void addtag(int p){for(p+=l-1,au[p]=x,av[p]=y;p;p>>=1)exi[p]=true;}

void solve(int x,int l,int r){
	if(!exi[x])return;
	int mid=(l+r)>>1,ls=x<<1,rs=ls|1,k=sk,fu,fv;
	for(auto e:E[x]){
		fu=find(e>>d),fv=find(e&lm);
		if(fu!=fv){
			if(sz[fu]<sz[fv]) swap(fu,fv);
			tu[++sk]=fu,tv[sk]=fv,fa[fv]=fu,sz[fu]+=sz[fv];
		}
	}
	if(l==r){
		writechar(find(au[x])==find(av[x])?'Y':'N');
		writechar('\n');
		return;
	}
	solve(ls,l,mid),solve(rs,mid+1,r);
	while(sk!=k){
		fa[tv[sk]]=tv[sk];
		sz[tu[sk]]-=sz[tv[sk]];
		sk--;
	}
}

int main(){
	gi(n),gi(m);
	int i,o,j;
	while(l<m)l<<=1;
	while(n>>d)d++;lm=(1<<d)-1;
	for(i=1;i<=n;i++)fa[i]=i,sz[i]=1;
	for(i=1;i<=m;i++){
		gi(o),gi(x),gi(y);
		if(x>y)swap(x,y);
		_O[i]=o;u[i]=x<<d|y;
		if(o==2)addtag(i);
	}
	for(i=1;i<=m;i++){
		j=u[i];
		if(_O[i]==0)lst[j]=i;
		if(_O[i]==1)addedge(lst[j],i,j),lst[j]=0;
	}
	for(i=1;i<=m;i++)if(lst[j=u[i]]==i)addedge(lst[j],l,j);
	solve(1,1,l);
	io::cbuf();
	cerr<<clock()<<endl; 
	return 0;
}
```

### 最小树形图

```c++
#include <bits/stdc++.h>

const int maxn=1e3+10;
const int maxm=1e5+10;

struct Edge{int u,v,length;}e[maxm];

int n,m,r,ans;
int id[maxn];
int pre[maxn];
int minv[maxn];
bool vis[maxn];
bool ins[maxn];

void dfs(int u,int& p){
	if (u==r)
		return;
	ins[u]=vis[u]=true;
	if (vis[pre[u]]==false)
		dfs(pre[u],p);
	else if (ins[pre[u]]){
		id[u]=++p;
		for (int v=pre[u];v!=u;v=pre[v])
			id[v]=p;
	}
	ins[u]=false;
	if (id[u]==0)id[u]=++p;
}

int main (){
#ifdef LOCAL
	freopen("dmst1.in","r",stdin);
#endif
	scanf("%d%d%d",&n,&m,&r);
	for (int i=1;i<=m;i++)
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].length);
	for (int p,c;"Robbery AK IOI";){
		memset(id,0,sizeof(id));
		memset(vis,0,sizeof(vis));
		memset(minv,0x3F,sizeof(minv));
		id[r]=p=1;c=0;
		for (int i=1;i<=m;i++)
			if (e[i].length<minv[e[i].v]){
				pre[e[i].v]=e[i].u;
				minv[e[i].v]=e[i].length;
			}
		for (int i=1;i<=n;i++)
			if (i!=r){
				if (minv[i]==0x3F3F3F3F)
					return puts("-1"),0;
				ans+=minv[i];
				if (vis[i]==false)
					dfs(i,p);
			}
		if (p==n)break;
		c=0;
		for (int i=1;i<=m;i++)
			if (id[e[i].u]!=id[e[i].v]){
				e[i].length-=minv[e[i].v];
				e[i].u=id[e[i].u];
				e[i].v=id[e[i].v];
				e[++c]=e[i];
			}
		m=c,n=p,r=id[r];
	}
	printf("%d\n",ans);
	return 0;
}
```

### 最小瓶颈路(多组询问路径 最大边权最小)

```c++
#include <cstdio>
#include <cstring>
#include <algorithm>
#define getchar() (*sS++)
#define Min(x,y) (fir[x]<fir[y]?x:y)
const int maxa=14;
const int maxm=1e5+3;
const int maxn=1e4+3;
struct Road{
	int to;
	int last;
}a[maxn];
struct Edge{
	int x,y;
	int dis;
	Edge(){}
	Edge(int a,int b,int c){x=a,y=b,dis=c;}
	bool operator <(const Edge&a)const{
		return dis<a.dis;
	}
}c[maxm];
int n;
int m;
int q;
int T;
int tot;
int num;
int bin[maxa];
int fir[maxn];
int Max[maxn];
int que[maxn];
int haha[maxn];
int head[maxn];
int pos[maxn<<1];
int f[maxn<<1][maxa];
char s[1<<21];
char *sS=s;
void Init();
void I(int&);
int Find(int);
void Dfs(int);
void Kruskal();
void HA(int,int);
int LCA(int,int);
int main(){
	fread(s,1,1<<21,stdin);
	I(n),I(m),I(q);
	for(register int i=1,x,y,z;i<=m;++i)
		I(x),I(y),I(z),c[i]=Edge(x,y,z);
	Kruskal();
	while(q--){
		register int x,y;I(x),I(y);
		if(Find(x)^Find(y))puts("-1");
		else printf("%d\n",Max[LCA(x,y)]);
	}return 0;
}
inline void I(int&x){
	register char ch;
	while(ch=getchar(),ch<'/');x=ch-'0';
	while(ch=getchar(),ch>'/')x=((x+(x<<2))<<1)+ch-'0';
}
inline void HA(int x,int y){
	a[++tot].to=y;
	a[tot].last=head[x];
	head[x]=tot;
}
inline int Find(int x){
	if(haha[x]==x)return x;
	return haha[x]=Find(haha[x]);
}
inline void Kruskal(){
	int k=0,num=n;
	std::sort(c+1,c+m+1);
	register int i,x,y;
	for(i=1;i<=n;++i)haha[i]=i;
	for(i=1;i<=m;++i){
		x=Find(c[i].x),y=Find(c[i].y);
		if(x==y)continue;
//		printf("%d %d\n",c[i].x,c[i].y);
		haha[x]=haha[y]=++num,haha[num]=num;
		Max[num]=c[i].dis,HA(num,x),HA(num,y);
		if((++k)==n-1)break;
	}
	for(i=num;i>n;--i)
		if(!fir[i])Dfs(i);
	Init();
}
#define y a[i].to
inline void Dfs(int x){
	fir[x]=++T,pos[T]=x;
	for(int i=head[x];i;i=a[i].last)
		Dfs(y),pos[++T]=x;
}
#undef y
inline void Init(){
	register int i,j;
	for(i=bin[0]=1;i<maxa;++i)bin[i]=bin[i-1]<<1;
	for(i=2,que[1]=0;i<=T;++i)que[i]=que[i>>1]+1;
	for(i=1;i<=T;++i)f[i][0]=pos[i];
	for(j=1;bin[j]<=T;++j)for(i=1;i+bin[j]-1<=T;++i)
		f[i][j]=Min(f[i][j-1],f[i+bin[j-1]][j-1]);
}
inline int LCA(int x,int y){
	x=fir[x],y=fir[y];
	if(x>y)std::swap(x,y);
	register int k=que[y-x+1];
	return Min(f[x][k],f[y-bin[k]+1][k]);
}
```



##  网络流

### Min_25费用流

```c++
#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstring>

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <functional>
#include <stack>
#include <queue>

#include <tuple>

#define getchar getchar_unlocked
#define putchar putchar_unlocked

#define _rep(_1, _2, _3, _4, name, ...) name
#define rep2(i, n) rep3(i, 0, n)
#define rep3(i, a, b) rep4(i, a, b, 1)
#define rep4(i, a, b, c) for (int i = int(a); i < int(b); i += int(c))
#define rep(...) _rep(__VA_ARGS__, rep4, rep3, rep2, _)(__VA_ARGS__)

using namespace std;

using i64 = long long;
using u8 = unsigned char;
using u32 = unsigned;
using u64 = unsigned long long;
using f80 = long double;

int get_int() {
  int n, c, sign = 0;
  while ((c = getchar()) < '-');
  if (c == '-') sign = 1, n = 0;
  else n = c - '0';
  while ((c = getchar()) >= '0') n = n * 10 + c - '0';
  return sign ? -n : n;
}

template <
  typename CapType, typename TotalCapType, 
  typename CostType, typename TotalCostType
>
class CostScaling {
private:
  static const int alpha = 8; // eps <- max(1, eps / alpha)

  using cap_t = CapType;
  using tcap_t = TotalCapType;
  using cost_t = CostType; // > max{|C|} * (2 * |V|)
  using tcost_t = TotalCostType;
  static constexpr cost_t Inf = (tcap_t(1) << (sizeof(tcap_t) * 8 - 2)) - 1;

  struct InputEdge { int from, to; cap_t b, c; cost_t cost; };
  struct Edge { int to, rev; cap_t cap; cost_t cost; };

  class Dinic {
  public:
    Dinic(int N, const vector<int>& ofs, vector<Edge>& edges, 
        vector<tcap_t>& capacity) 
      : N(N), ofs(ofs), edges(edges), capacity(capacity), last(N) {}

    bool succeeded() {
      // s -> u: capacity[u]
      // u -> t: capacity[u + N]
      tcap_t f = 0;
      for (int u = 0; u < N; ++u) f += capacity[u];
      vector<int> que(N);
      while (f) {
        dist.assign(N, -1);
        int qh = 0, qt = 0, lv = N;
        for (int u = 0; u < N; ++u) if (capacity[u] > 0) que[qt++] = u, dist[u] = 0;
        for (; qh < qt; ) {
          int u = que[qh++];
          if (lv == N && capacity[u + N] > 0) lv = dist[u];
          if (dist[u] > lv) break;
          for (int ei = ofs[u]; ei < ofs[u + 1]; ++ei) {
            int v = edges[ei].to;
            if (edges[ei].cap > 0 && dist[v] == -1) {
              que[qt++] = v, dist[v] = dist[u] + 1;
            }
          }
        }
        if (lv == N) break;
        for (int u = 0; u < N; ++u) last[u] = ofs[u];
        for (int u = 0; u < N; ++u) if (capacity[u] > 0) {
          auto df = block_flow(u, capacity[u]);
          f -= df, capacity[u] -= df;
        }
      }
      return f == 0;
    }

  private:
    tcap_t block_flow(int u, tcap_t f) {
      tcap_t ret = 0;
      if (capacity[u + N] > 0) {
        tcap_t df = min(f, capacity[u + N]);
        capacity[u + N] -= df;
        return df;
      }
      for (auto& ei = last[u]; ei < ofs[u + 1]; ++ei) {
        auto& e = edges[ei]; int v = e.to;
        if (e.cap == 0 || dist[v] <= dist[u]) continue;
        cap_t df = block_flow(v, min<cap_t>(e.cap, f));
        if (df == 0) continue;
        e.cap -= df, edges[e.rev].cap += df;
        f -= df, ret += df;
        if (f == 0) break;
      }
      return ret;
    }

    int N;
    const vector<int>& ofs;
    vector<Edge>& edges;
    vector<tcap_t>& capacity;
    vector<int> last, dist;
  };

public:
  CostScaling(int N, int M=0) : N(N), capacity(2 * N) {
    if (M > 0) in.reserve(M);
  }

  void add_directed_edge(int u, int v, cap_t b, cap_t c, cost_t cost) {
    if (b > 0) capacity[v] += b, capacity[u + N] += b;
    else capacity[u] += -b, capacity[v + N] += -b;
    in.push_back({u, v, b, c, cost});
  }

  pair<bool, tcost_t> minimum_cost_circulation() {
    construct();
    if (!has_feasible_circulation()) return {false, 0};

    const int cost_multiplier = 2 << __lg(N); // should be > |V|
    cost_t eps = 0;
    for (auto& e : edges) e.cost *= cost_multiplier, eps = max(eps, e.cost);
    
    while (eps > 1) refine(eps = max<cost_t>(1, eps / alpha));

    tcost_t ret = initial_cost;
    for (auto& e : edges) ret -= (e.cost / cost_multiplier) * e.cap;
    return {true, ret / 2};
  }

private:
  void refine(const cost_t eps) {
    auto cost_p = [&] (int u, const Edge& e) {
      return e.cost + potential[u] - potential[e.to];
    };
    for (int u = 0; u < N; ++u) for (int i = ofs[u]; i < ofs[u + 1]; ++i) {
      auto& e = edges[i];
      if (cost_p(u, e) < 0) edges[e.rev].cap += e.cap, e.cap = 0;
    }
    vector<tcap_t> excess(initial_excess);
    for (auto& e : edges) excess[e.to] -= e.cap;

    vector<int> stack; stack.reserve(N);
    for (int u = 0; u < N; ++u) if (excess[u] > 0) stack.push_back(u);

    auto residue = [&] (const Edge& e) -> cap_t { return e.cap; };
    auto push = [&] (int u, Edge& e, cap_t df) {
      e.cap -= df; edges[e.rev].cap += df;
      excess[e.to] += df; excess[u] -= df;
      if (excess[e.to] > 0 && excess[e.to] <= df) {
        stack.push_back(e.to);
      }
    };
    auto relabel = [&] (int u, cost_t delta) {
      potential[u] -= delta + eps;
    };
    auto relabel_in_advance = [&] (int u) {
      if (excess[u] != 0) return false;
      auto delta = Inf;
      for (int ei = ofs[u]; ei < ofs[u + 1]; ++ei) {
        auto& e = edges[ei];
        if (residue(e) == 0) continue;
        if (cost_p(u, e) < 0) return false;
        else delta = min<tcost_t>(delta, cost_p(u, e));
      }
      relabel(u, delta);
      return true;
    };
    auto discharge = [&] (int u) {
      auto delta = Inf;
      for (int ei = ofs[u]; ei < ofs[u + 1]; ++ei) {
        auto& e = edges[ei];
        if (residue(e) == 0) continue;
        if (cost_p(u, e) < 0) {
          if (relabel_in_advance(e.to)) {
            --ei; continue; // modify ei (!)
          }
          cap_t df = min<tcap_t>(excess[u], residue(e));
          push(u, e, df);
          if (!excess[u]) return;
        } else delta = min<tcost_t>(delta, cost_p(u, e));
      }
      relabel(u, delta);
      stack.push_back(u);
    };
    while (!stack.empty()) {
      auto u = stack.back(); stack.pop_back();
      discharge(u);
    }
  }

  void construct() {
    ofs.assign(N + 1, 0);
    edges.resize(2 * in.size());
    initial_excess.assign(N, 0);
    initial_cost = 0;
    potential.assign(N, 0);
    for (auto& e : in) ofs[e.from + 1]++, ofs[e.to + 1]++;
    for (int i = 1; i <= N; ++i) ofs[i] += ofs[i - 1];
    for (auto& e : in) {
      initial_excess[e.to] += e.c;
      initial_excess[e.from] += -e.b;
      initial_cost += tcost_t(e.cost) * (e.c + e.b);
      edges[ofs[e.from]++] = {e.to, ofs[e.to], e.c - e.b, e.cost};
      edges[ofs[e.to]++] = {e.from, ofs[e.from] - 1, 0, -e.cost};
    }
    for (int i = N; i > 0; --i) ofs[i] = ofs[i - 1];
    ofs[0] = 0;
  }

  bool has_feasible_circulation() {
    return Dinic(N, ofs, edges, capacity).succeeded();
  }

private:
  int N; 
  vector<InputEdge> in;
  vector<tcap_t> capacity;

  vector<int> ofs;
  vector<Edge> edges;

  tcost_t initial_cost;
  vector<tcap_t> initial_excess;
  vector<tcost_t> potential;
};
// cap, total_cap, cost * (2 * |V|), total_cost
using MCC = CostScaling<int64_t, int64_t, int64_t, int64_t>;
// using MCC = CostScaling<int, int, int, int>;

void solve() {
  int N, M;
  while (~scanf("%d %d", &N, &M)) {
    MCC mcc1(N, M), mcc2(N, M);
    rep(i, M) {
      int u = get_int() - 1, v = get_int() - 1;
      int c = get_int(), cost = get_int();
      mcc1.add_directed_edge(u, v, 0, c, 0);
      mcc2.add_directed_edge(u, v, 0, c, cost);
    }
    mcc1.add_directed_edge(N - 1, 0, 0, 1e18, -1);
    auto max_flow = -mcc1.minimum_cost_circulation().second;
    mcc2.add_directed_edge(N - 1, 0, max_flow, max_flow, 0);
    printf("%lld %lld\n", max_flow, mcc2.minimum_cost_circulation().second);
  }
}
```

### HLPP最大流

```c++
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define ll long long
#define re register
#define gc get_char
#define cs const

namespace IO{
	inline char get_char(){
		static cs int Rlen=1<<20|1;
		static char buf[Rlen],*p1,*p2;
		return (p1==p2)&&(p2=(p1=buf)+fread(buf,1,Rlen,stdin),p1==p2)?EOF:*p1++;
	}
	
	inline int getint(){
		re char c;
		while(!isdigit(c=gc()));re int num=c^48;
		while(isdigit(c=gc()))num=(num+(num<<2)<<1)+(c^48);
		return num;
	}
}
using namespace IO;

using std::cerr;
using std::cout;

cs int N=1203;
cs int INF=0x3f3f3f3f;
int n,m;
struct edge{
	int to,cap,rev;
	edge(cs int &_to,cs int &_cap,cs int &_rev):to(_to),cap(_cap),rev(_rev){}
};

std::vector<edge> G[N];
inline void addedge(int u,int v,int val){
	G[u].push_back(edge(v,val,G[v].size()));
	G[v].push_back(edge(u,0,G[u].size()-1));
} 

std::vector<int> lst[N],gap[N];
int rest[N];
int ht,h[N],cnt[N],work;
int S,T;

inline void upd_h(int v,int nh){
	++work;
	if(h[v]!=INF)--cnt[h[v]];
	h[v]=nh;
	if(nh==INF)return ;
	++cnt[nh],ht=nh;
	gap[nh].push_back(v);
	if(rest[v])lst[nh].push_back(v);
}

inline void relabel(){
	work=0;
	memset(h,0x3f,sizeof h);
	memset(cnt,0,sizeof cnt);
	for(int re i=0;i<=ht;++i)lst[i].clear(),gap[i].clear();
	h[T]=0;
	std::queue<int> q;q.push(T);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(edge &e:G[u])if(h[e.to]==INF&&G[e.to][e.rev].cap)
		q.push(e.to),upd_h(e.to,h[u]+1);
		ht=h[u];
	} 
}

inline void push(int u,edge &e){
	if(rest[e.to]==0)lst[h[e.to]].push_back(e.to);
	int delta=std::min(rest[u],e.cap);
	e.cap-=delta;
	G[e.to][e.rev].cap+=delta;
	rest[u]-=delta;
	rest[e.to]+=delta;
}

inline void push_flow(int u){
	int nh=INF;
	for(edge &e:G[u])if(e.cap){
		if(h[u]==h[e.to]+1){
			push(u,e);
			if(rest[u]<=0)return ;
		}
		else nh=std::min(nh,h[e.to]+1);
	}
	if(cnt[h[u]]>1)upd_h(u,nh);
	else for(int re i=h[u];i<N;++i){
		for(int j:gap[i])upd_h(j,INF);
		gap[i].clear();
	}
}

inline int HLPP(int lim=20000){
	memset(rest,0,sizeof rest);
	rest[S]=2147483647;//,rest[T]=-INF;
	relabel();
	for(edge &e:G[S])push(S,e);
	for(;~ht;--ht)
	while(!lst[ht].empty()){
		int u=lst[ht].back();
		lst[ht].pop_back();
		push_flow(u);
		if(work>lim)
		relabel();
	}
	return rest[T];
}

signed main(){
//	freopen("test.in","r",stdin);
	n=getint(),m=getint();
	S=getint(),T=getint();
	for(int re i=1,u,v,val;i<=m;++i){
		u=getint(),v=getint(),val=getint();
		addedge(u,v,val);
	}
	cout<<HLPP()<<"\n";
	return 0;
}
```



### 无源汇有上下界可行流

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=210,M=20810,INF=1e9;
int sum[N],S,T,num=1,to[M],c[M],la[M],he[N],preflow[M],d[N],cur[N],maxflow;
queue<int>q;
int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch&15),ch=getchar();
	return x*f;
}
void addedge(int x,int y,int ca)
{
	to[++num]=y;c[num]=ca;la[num]=he[x];he[x]=num;
	to[++num]=x;c[num]=0;la[num]=he[y];he[y]=num;
}
bool BFS()
{
	memset(d,-1,sizeof(d));while (!q.empty()) q.pop();
	d[S]=1;q.push(S);
	while (!q.empty())
	{
		int u=q.front();q.pop();
		for (register int i=he[u];i;i=la[i])
		{
			int v=to[i];
			if (c[i]&&d[v]==-1)
			{
				d[v]=d[u]+1;q.push(v);
				if (v==T) return 1;
			}
		}
	}
	return 0;
}
int DFS(int u,int flow)
{
	if (u==T||!flow) return flow;
	int rest=flow;
	for (register int i=cur[u];i;i=la[i])
	{
		int v=to[i];cur[u]=i;
		if (c[i]&&d[u]+1==d[v])
		{
			int k=DFS(v,min(rest,c[i]));
			if (!k) {d[v]=-1;continue;}
			rest-=k;c[i]-=k;c[i^1]+=k;
			if (!rest) return flow;
		}
	}
	return flow-rest;
}
void Dinic()
{
	while (BFS())
	{
		memcpy(cur,he,sizeof(he));
		maxflow+=DFS(S,INF);
	}
}
int main()
{
	int n=read(),m=read();
	for (register int i=1;i<=m;++i)
	{
		int x=read(),y=read(),lower=read(),upper=read();
		sum[x]+=lower;sum[y]-=lower;addedge(x,y,upper-lower);preflow[i]=upper;
	}
	S=n+1;T=S+1;int sumflow=0;
	for (register int i=1;i<=n;++i) if (sum[i]>0) addedge(i,T,sum[i]),sumflow+=sum[i]; else addedge(S,i,-sum[i]);
	Dinic();
	if (maxflow<sumflow) {printf("NO\n");return 0;}
	printf("YES\n");
	for (register int i=1;i<=m;++i) printf("%d\n",preflow[i]-c[i<<1]);
	return 0;
}
```



### 有源汇有上下界最大流

```c++
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

template <typename T>void read(T &t)
{
	t=0;int f=0;char c=getchar();
	while(!isdigit(c)){f|=c=='-';c=getchar();}
	while(isdigit(c)){t=t*10+c-'0';c=getchar();}
	if(f)t=-t;
}

const ll inf=0x3f3f3f3f3f3f3f3f;
const int maxn=202+5,maxm=9999+5;
int n,m,s,t;
int ss,tt;

struct edge
{
	int u,v,nxt;
	ll f;
}g[maxm<<2];

int head[maxn],ecnt=1;
void eADD(int u,int v,ll f)
{
	g[++ecnt].u=u;g[ecnt].v=v;g[ecnt].f=f;g[ecnt].nxt=head[u];head[u]=ecnt;
	g[++ecnt].u=v;g[ecnt].v=u;g[ecnt].f=0;g[ecnt].nxt=head[v];head[v]=ecnt;
}

ll A[maxn];

int dep[maxn],cur[maxn];
bool BFS()
{
	queue<int> q;
	for(register int i=1;i<=n;++i)
		dep[i]=0,cur[i]=head[i];
	dep[ss]=dep[tt]=0,cur[ss]=head[ss],cur[tt]=head[tt];
	dep[ss]=1;
	q.push(ss);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(register int i=head[u];i;i=g[i].nxt)
		{
			int v=g[i].v;
			if(!dep[v] && g[i].f)
			{
				dep[v]=dep[u]+1;
				if(v==tt)return true;
				q.push(v);
			}
		}
	}
	return false;
}

ll dfs(int u,ll infl)
{
	if(u==tt)return infl;
	ll rest=infl;
	for(register int i=cur[u];i && rest;i=g[i].nxt)
	{
		int v=g[i].v;
		cur[u]=i;
		if(g[i].f && dep[v]==dep[u]+1)
		{
			ll flow=dfs(v,min(rest,g[i].f));
			rest-=flow;
			g[i].f-=flow;
			g[i^1].f+=flow;
		}
	}
	return infl-rest;
}

int main()
{
	read(n),read(m),read(s),read(t);
	ss=n+1,tt=n+2;
	for(register int i=1;i<=m;++i)
	{
		int u,v;
		ll up,low;
		read(u),read(v),read(low),read(up);
		eADD(u,v,up-low);
		A[u]-=low;
		A[v]+=low;
	}
	eADD(t,s,inf);
	ll tot=0;
	for(register int i=1;i<=n;++i)
		if(A[i]<0)
			eADD(i,tt,-A[i]);
		else if(A[i]>0)
			eADD(ss,i,A[i]),tot+=A[i];
	ll ans=0;
	while(BFS())
		ans+=dfs(ss,inf);
	if(ans<tot)
	{
		puts("please go home to sleep");
		return 0;
	}
	ans=0;
	ss=s,tt=t;
	while(BFS())
		ans+=dfs(ss,inf);
	printf("%lld",ans);
	return 0;
}
```



### 有源汇有上下界最小流

```c++
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define ll long long
static char buf[100000],*pa,*pd;
#define gc pa==pd&&(pd=(pa=buf)+fread(buf,1,100000,stdin),pa==pd)?EOF:*pa++
inline int read(){
 	register int x(0);register char c(gc);
	while(c>'9'||c<'0')c=gc;
	while(c>='0'&&c<='9')x=x*10+c-48,c=gc;
	return x;
} 
const int N=510000;
const ll INF=987654321987654321;
struct edge{
 	int to,next;
	ll w;
}e[N];
int head[51000],vis[51000],tot=1,deep[110000];
void add(int x,int y,ll z){
 	e[++tot].next=head[x];e[tot].to=y;e[tot].w=z;head[x]=tot;
	e[++tot].next=head[y];e[tot].to=x;e[tot].w=0;head[y]=tot;
} 
ll out[N],sum,ans;
queue<int> q;
int n,m,s,t,S=0,T=51000-1;
bool BFS(){
	memset(deep,-1,sizeof(deep));
 	deep[S]=0;
	q.push(S);
	while(!q.empty()){
	 	int u=q.front();q.pop();
	//	cout<<u<<' '<<deep[u]<<'\n';
		for(int i=head[u];i;i=e[i].next)
			if(deep[e[i].to]<0&&e[i].w){
			 	deep[e[i].to]=deep[u]+1;
				q.push(e[i].to);
			} 
	}
	//cout<<deep[T]<<'\n';
	return deep[T]>0;
} 
ll DFS(int u,ll MIN){
 	int a=0,b;
	if(u==T||!MIN)return MIN;
	for(int &i=vis[u];i;i=e[i].next)
		if(e[i].w&&deep[e[i].to]==deep[u]+1&&(b=DFS(e[i].to,min(MIN,e[i].w)))){
		 	a+=b;
			e[i].w-=b;
			MIN-=b;
			e[i^1].w+=b;
			if(!MIN)break;
		} 
	if(!a)deep[u]=-1;
	return a;
} 
int main(){
//	freopen("1.in","r",stdin);
	n=read();m=read();s=read();t=read();
	register int i,x,y,a,b;
	for(i=1;i<=m;i++){
	 	x=read();y=read();a=read();b=read();
		add(x,y,b-a);
		out[x]+=a;
		out[y]-=a;
	} 
	for(i=1;i<=n;i++){
		//cout<<i<<' '<<out[i]<<'\n';
	 	if(out[i]>0)add(i,T,out[i]),sum+=out[i];
		if(out[i]<=0)add(S,i,-out[i]);
	}
	//cout<<ans<<'\n';
	while(BFS()){
		//cout<<ans;
		memcpy(vis,head,sizeof(vis));
	 	ans+=DFS(S,INF);
	} 
	add(t,s,INF);
	while(BFS()){
		memcpy(vis,head,sizeof(vis));
	 	ans+=DFS(S,INF);
	}
	//cout<<ans<<' '<<sum<<'\n';
	if(ans!=sum){
	 	cout<<"please go home to sleep";
		return 0;
	} 
	cout<<e[tot].w;
 	return 0;
} 
```



##  字符串

### 子串出现个数 KMP

```c++
#include<bits/stdc++.h>
using namespace std;
char a[1000005],b[1000005];
int ans,p[1000005],n,m;
inline void pre(){
	p[1]=0;
	int j=0;
	for (int i=1;i<m;i++){
		while(j&&b[j+1]!=b[i+1]) j=p[j];
		if(b[j+1]==b[i+1]) j++;
		p[i+1]=j;
	}
}
inline void kmp(){
	int j=0;
	for (int i=0;i<n;i++){
		while(j&&b[j+1]!=a[i+1]) j=p[j];
		if(b[j+1]==a[i+1]) j++;
		if(j==m) ans++,j=p[j];
	}
}
int main(){
//	freopen("#103.in","r",stdin);
//	freopen("#103.out","w",stdout);
	scanf("%s",a+1);
	scanf("%s",b+1);
	n=strlen(a+1);
	m=strlen(b+1);
	pre();
	kmp();
	printf("%d\n",ans);
	return 0;
}
```

### 回文子串 （支持前后添加字符串）（在前面添加为反序）

```c++
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#define N 400050
int ch[N][26],fail[N],len[N],cnt=1,lst1,lst2,dep[N];
int Q[N<<1],l,r,n;ll ans;char w[N];
void push_back(int i) {
	int p=lst1,x=Q[i]-'a';
	for(;Q[i]!=Q[i-len[p]-1];p=fail[p]);
	if(!ch[p][x]) {
		int np=++cnt,q=fail[p];
		for(;Q[i]!=Q[i-len[q]-1];q=fail[q]);
		len[np]=len[p]+2,fail[np]=ch[q][x],dep[np]=dep[fail[np]]+1;
		ch[p][x]=np;
	}
	lst1=ch[p][x];
	ans+=dep[lst1];
	if(len[lst1]==r-l+1) lst2=lst1;
}
void push_front(int i) {
	int p=lst2,x=Q[i]-'a';
	for(;Q[i]!=Q[i+len[p]+1];p=fail[p]);
	if(!ch[p][x]) {
		int np=++cnt,q=fail[p];
		for(;Q[i]!=Q[i+len[q]+1];q=fail[q]);
		len[np]=len[p]+2,fail[np]=ch[q][x],dep[np]=dep[fail[np]]+1;
		ch[p][x]=np;
	}
	lst2=ch[p][x];
	ans+=dep[lst2];
	if(len[lst2]==r-l+1) lst1=lst2;
}
int main() {
	fail[0]=fail[1]=1; len[1]=-1;
	scanf("%s",w+1);
	l=N,r=N-1;
	int i;
	n=strlen(w+1);
	for(i=1;i<=n;i++) Q[++r]=w[i],push_back(r);
	int m,o;
	scanf("%d",&m);
	while(m--) {
		scanf("%d",&o);
		if(o==1) {
			scanf("%s",w+1);
			n=strlen(w+1);
			for(i=1;i<=n;i++) {
				Q[++r]=w[i];
				push_back(r);
			}
		}else if(o==2) {
			scanf("%s",w+1);
			n=strlen(w+1);
			for(i=1;i<=n;i++) {
				Q[--l]=w[i];
				push_front(l);
			}
		}else {
			printf("%lld\n",ans);
		}
	}
}
```

### 后缀数组（SA-IS）

读入一个长度为n的由大小写英文字母或数字组成的字符串，请把这个字符串的所有非空后缀按字典序从小到大排序，然后按顺序输出后缀的第一个字符在原串中的位置。位置编号为1到n。

```c++
#include <cstdio>
#include <algorithm>
#include <numeric>
#include <cstring>

struct IO_Tp {
    const static int _O_Buffer_Size = 10 << 20;
    char _O_Buffer[_O_Buffer_Size], *_O_pos = _O_Buffer;

    ~IO_Tp() { fwrite(_O_Buffer, 1, _O_pos - _O_Buffer, stdout); }

    IO_Tp &operator<<(int n) {
        static char _buf[10];
        char *_pos = _buf;
        do
            *_pos++ = '0' + n % 10;
        while (n /= 10);
        while (_pos != _buf) *_O_pos++ = *--_pos;
        return *this;
    }

    IO_Tp &operator<<(char ch) {
        *_O_pos++ = ch;
        return *this;
    }
} IO;

const int Max_N = 1000005;

namespace SA_IS {
int *sa;

template <typename _Char>
void sais_core(const int n, const int m, const _Char s[], char type[], int lms[], int cnt[]) {
    int n1 = 0, ch = -1;

    type[n - 1] = 1;
    for (int i = n - 2; i >= 0; --i) type[i] = s[i] == s[i + 1] ? type[i + 1] : s[i] < s[i + 1];

    std::fill(cnt, cnt + m, 0);
    for (int i = 0; i < n; ++i) ++cnt[static_cast<int>(s[i])];
    std::partial_sum(cnt, cnt + m, cnt);

    auto induced_sort = [&](const int v[]) {
        std::fill(sa, sa + n, 0);

        int *cur = cnt + m;
        auto push_S = [&](const int x) { sa[--cur[static_cast<int>(s[x])]] = x; };
        auto push_L = [&](const int x) { sa[cur[static_cast<int>(s[x])]++] = x; };

        std::copy(cnt, cnt + m, cur);
        for (int i = n1 - 1; i >= 0; --i) push_S(v[i]);

        std::copy(cnt, cnt + m - 1, cur + 1);
        for (int i = 0; i < n; ++i)
            if (sa[i] > 0 && type[sa[i] - 1] == 0)
                push_L(sa[i] - 1);

        std::copy(cnt, cnt + m, cur);
        for (int i = n - 1; i >= 0; --i)
            if (sa[i] > 0 && type[sa[i] - 1])
                push_S(sa[i] - 1);
    };

    for (int i = 1; i < n; ++i)
        if (type[i - 1] == 0 && type[i] == 1)
            type[i] = 2, lms[n1++] = i;
    induced_sort(lms);

    auto lms_equal = [&](int x, int y) {
        if (s[x] == s[y])
            while (s[++x] == s[++y] && type[x] == type[y])
                if (type[x] == 2 || type[y] == 2)
                    return true;
        return false;
    };

    int *s1 = std::remove_if(sa, sa + n, [&](const int x) { return type[x] != 2; });
    for (int i = 0; i < n1; ++i) s1[sa[i] >> 1] = ch += ch <= 0 || !lms_equal(sa[i], sa[i - 1]);
    for (int i = 0; i < n1; ++i) s1[i] = s1[lms[i] >> 1];

    if (ch + 1 < n1)
        sais_core(n1, ch + 1, s1, type + n, lms + n1, cnt + m);
    else
        for (int i = 0; i < n1; ++i) sa[s1[i]] = i;

    for (int i = 0; i < n1; ++i) lms[n1 + i] = lms[sa[i]];
    induced_sort(lms + n1);
}

template <typename _Char>
void main(const _Char s[], const int n, const int m) {
    static int _lms[Max_N], _cnt[Max_N << 1];
    static char _type[Max_N << 1];
    sais_core(n + 1, m, s, _type, _lms, _cnt);
}
}  // namespace SA_IS

char s[Max_N];
int N;
int sa[Max_N];

int main(int argc, char **argv) {
    scanf("%s", s);
    N = strlen(s);

    SA_IS::sa = sa;
    SA_IS::main(s, N, 128);

    for (int i = 1; i <= N; ++i) IO << sa[i] + 1 << " \n"[i == N];

    return 0;
}
```



##  数据结构

### 普通平衡树（增 删 排名 k大 前驱 后继）

```c++
#include<cstdio>
#include<algorithm>
#define N 100005
using namespace std;
struct io_t{
	char p[1<<20],*s;
	char e[1<<20],*t;
	int a[24];
	io_t():s(p),t(e){
		fread(s,1,
		sizeof p,stdin);
	}
	~io_t(){
		fwrite(e,1,
		t-e,stdout);
	}
	operator int(){
		static int v,j;
		v=0,j=1;
		while(*s<48)
			j=*s++^45;
		do
			v=v*10+*s++-48;
		while(*s>32);
		return j?v:-v;
	}
	void print(int v){
		static int* q=a;
		if(!v)*t++=48;
		else{
			if(v<0)
				*t++=45,
				v*=-1;
			while(v)
				*q++=v%10+48,
				v/=10;
			while(q!=a)
				*t++=*--q;
		}
		*t++=10;
	}
}ip;
int f[N],a[N],u[N],v[N];
int m,z=ip;
int foo(int i){
	int j=1;
	for(--i;i;i^=i&-i)
		j+=a[i];
	return j;
}
int add(int i,int j){
	for(;i<=m;i+=i&-i)
		a[i]+=j;
}
int bar(int v){
	int s=0;
	for(int j=1<<16;j;j>>=1)
		if(s+j<=m
		&&v>a[s+j])
			v-=a[s+=j];
	return s;
}
int pre(int i){
	for(--i;;i^=i&-i)
		if(a[i]){
			int j=i&-i,s=i^j,v=a[i];
			for(;j;j>>=1)
				if(s+j<=m
				&&v>a[s+j])
					v-=a[s+=j];
			return s;
		}
}
int main(){
	for(int i=0;i!=z;++i){
		u[i]=ip,v[i]=ip;
		if(u[i]==1)
			f[m++]=v[i];
	}
	sort(f,f+m);
	m=unique(f,f+m)-f;
	for(int i=0;i!=z;++i){
		int k=u[i],s=v[i];
		if(k==6)
			s=upper_bound(f,f+m,s)-f;
		else if(k!=4)
			s=lower_bound(f,f+m,s)-f+1;
		if(k==1)
			add(s,1);
		if(k==2)
			add(s,-1);
		if(k==3)
			ip.print(foo(s));
		if(k==4)
			ip.print(f[bar(s)]);
		if(k==5)
			ip.print(f[pre(s)]);
		if(k==6)
			ip.print(f[bar(foo(s+1))]);
	}
}
```

```c++
#include<bits/stdc++.h>
using namespace std;
vector<int> v;
int main(){
	int n,op,x;
	scanf("%d",&n);
	while(n--){
		scanf("%d %d",&op,&x);
		switch (op){
			case 1:v.insert(upper_bound(v.begin(),v.end(),x),x);break;
			case 2:v.erase(lower_bound(v.begin(),v.end(),x));break;
			case 3:cout<<lower_bound(v.begin(),v.end(),x)-v.begin()+1<<endl;break;
			case 4:cout<<v[x-1]<<endl;break;
			case 5:cout<<*--lower_bound(v.begin(),v.end(),x)<<endl;break;
			case 6:cout<<*upper_bound(v.begin(),v.end(),x)<<endl;break;
		}
	} 
	return 0;
} 
```



### 文艺平衡树(区间翻转)

```c++
#include<algorithm>
#include<cstdio>
#define Z(o)(o->i->s+1)
#define M (i+j>>1)
using std::swap;
struct buf{
	char z[1<<21],*s;
	char e[1<<20],*p;
	buf():s(z),p(e){
		z[fread(z,1,sizeof z,stdin)]=0;
	}
	~buf(){fwrite(e,1,p-e,stdout);}
	operator int(){
		int x=0;
		while(*s<48)++s;
		while(*s>32)
			x=x*10+*s++-48;
		return x;
	}
	void out(int x){
		static char z[12];
		char*i=z;
		if(!x)*p++=48;
		else{
			while(x){
				int y=x/10;
				*i++=x-y*10+48,x=y;
			}
			while(i!=z)*p++=*--i;
		}
		*p++=32;
	}
}it;
const int N=1e5+5;
typedef struct node*ptr;
struct node{
	int v,s;
	ptr i,j;
	bool r;
	ptr up(){s=i->s+1+j->s;return this;}
	void down(){
		if(r)i->r^=1,j->r^=1,swap(i,j),r=0;
	}
}e[N];
ptr a=e;
ptr get(int v,int s,ptr i,ptr j){
	return&(*++a=(node){v,s,i,j});
}
ptr pre(int i,int j){
	return i>j?e:get(M,j-i+1,pre(i,M-1),pre(M+1,j));
}
void zig(ptr&o,ptr&s){ptr t=o->i;o->i=s,s=o->up(),o=t;}
void zag(ptr&o,ptr&s){ptr t=o->j;o->j=s,s=o->up(),o=t;}
ptr splay(int v,ptr&o){
	ptr s=e,t=e;
	while(1){
		o->down();
		if(v==Z(o))break;
		if(v<Z(o)){
			o->i->down();
			if(v<Z(o->i))
				zig(o,o->i->j);
			zig(o,s);
		}else{
			v-=Z(o);
			o->j->down();
			if(v>Z(o->j))
				v-=Z(o->j),zag(o,o->j->i);
			zag(o,t);
		}
	}
	while(s!=e)zig(s,o->j);
	while(t!=e)zag(t,o->i);
	return o->up();
}
ptr&splay(int s,int t,ptr&o){
	splay(s,o);
	return splay(t-s+2,o->j)->i;
}
void out(ptr o){
	if(o!=e){
		o->down();
		out(o->i);
		it.out(o->v);
		out(o->j);
	}
}
int main(){
	int n=it,m=it;
	ptr r=pre(0,n+1);
	while(m--){int s=it;splay(s,it,r)->r^=1;}
	out(splay(1,n,r));
}
```



### 二逼平衡树（点修改 区间查询 区间排名 区间前驱 区间后继）

```c++
/*All my love*/
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double D;
typedef pair<int,int> Pii;
template<class _T>inline void rd(_T&_a){int _ch,_f=0;while(!isdigit(_ch=getchar()))_f=_ch=='-';_a=_ch-'0';while(isdigit(_ch=getchar()))_a=_a*10+_ch-'0';if(_f)_a=-_a;}
template<class _T>inline _T dmin(const _T _a,const _T _b){return _a<_b?_a:_b;}
template<class _T>inline _T dmax(const _T _a,const _T _b){return _a>_b?_a:_b;}
template<class _T>inline bool cmin(_T&_a,const _T _b){return _a>_b?_a=_b,1:0;}
template<class _T>inline bool cmax(_T&_a,const _T _b){return _a<_b?_a=_b,1:0;}
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)
#define fir first
#define sec second
#define LC t[r0].l,l,m
#define RC t[r0].r,m+1,r
const int inf=0x3f3f3f3f;
const D eps=1e-8;
const int N=5e4+5;
struct tree{int l,r,sz;}t[N<<6];
int P,X,rt[N],rt0[N],lr[N],rr[N],lc,rc,idx,ct,b[N<<1],a[N],op[N],opl[N],opr[N],opx[N];
void U0(int&r1,int r0,int l,int r){
	t[r1=++idx]=t[r0];t[r1].sz++;
	if(l==r)return;
	int m=l+r>>1;if(P>m)U0(t[r1].r,RC);else U0(t[r1].l,LC);
}
void U1(int&r0,int l,int r){
	if(!r0)r0=++idx;t[r0].sz+=X;
	if(l==r)return;
	int m=l+r>>1;if(P>m)U1(RC);else U1(LC);
}
void Rt(int l,int r){
	lc=rc=0;lr[0]=rt0[l];rr[0]=rt0[r];
	for(;l;l^=(l&-l))lr[++lc]=rt[l];
	for(;r;r^=(r&-r))rr[++rc]=rt[r];
}
void Gl(){for(int i=0;i<=lc;i++)lr[i]=t[lr[i]].l;for(int i=0;i<=rc;i++)rr[i]=t[rr[i]].l;}
void Gr(){for(int i=0;i<=lc;i++)lr[i]=t[lr[i]].r;for(int i=0;i<=rc;i++)rr[i]=t[rr[i]].r;}
int Ls(){int r=0;for(int i=0;i<=lc;i++)r-=t[t[lr[i]].l].sz;for(int i=0;i<=rc;i++)r+=t[t[rr[i]].l].sz;return r;}
void Rk(){
	X=0;int l=1,r=ct;
	while(r>P){
		int m=l+r>>1;
		if(P>m)X+=Ls(),l=m+1,Gr();
		else r=m,Gl();
	}
	for(int i=0;i<=lc;i++)X-=t[lr[i]].sz;
	for(int i=0;i<=rc;i++)X+=t[rr[i]].sz;
}
void Qy(){
	int l=1,r=ct;
	while(l<r){
		int m=l+r>>1,tmp=Ls();
		if(tmp>=P)r=m,Gl();else l=m+1,P-=tmp,Gr();
	}
	X=l;
}
int main(){
	//freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);
	int n,m;rd(n);rd(m);
	for(int i=1;i<=n;i++)rd(a[i]),b[++ct]=a[i];
	for(int i=1;i<=m;i++){rd(op[i]);rd(opl[i]);rd(opr[i]);if(op[i]^3){rd(opx[i]);if(op[i]^2)b[++ct]=opx[i];}else b[++ct]=opr[i];}
	sort(b+1,b+ct+1);ct=unique(b+1,b+ct+1)-b-1;
	for(int i=1;i<=n;i++)P=a[i]=lower_bound(b+1,b+ct+1,a[i])-b,U0(rt0[i],rt0[i-1],1,ct);
	for(int i=1;i<=m;i++){
		int l=opl[i],r=opr[i],x=opx[i];
		switch(op[i]){
			case 1:Rt(l-1,r);P=lower_bound(b+1,b+ct+1,x)-b-1;Rk();printf("%d\n",X+1);break;
			case 2:Rt(l-1,r);P=x;Qy();printf("%d\n",b[X]);break;
			case 3:P=a[l];X=-1;for(int p=l;p<=n;p+=(p&-p))U1(rt[p],1,ct);
				   P=a[l]=lower_bound(b+1,b+ct+1,r)-b;X=1;for(int p=l;p<=n;p+=(p&-p))U1(rt[p],1,ct);break;
			case 4:Rt(l-1,r);P=lower_bound(b+1,b+ct+1,x)-b-1;Rk();P=X;Rt(l-1,r);Qy();printf("%d\n",b[X]);break;
			case 5:Rt(l-1,r);P=lower_bound(b+1,b+ct+1,x)-b;Rk();P=X+1;Rt(l-1,r);Qy();printf("%d\n",b[X]);break;
		}
	}
	return 0;
}
/*Said it don't*/
```



### 三维偏序 CDQ分治

```c++
#include <bits/stdc++.h>
#define ll long long
#define N 200010
using namespace std;
ll read() {
	ll x=0,f=1; char ch=getchar();
	for (;ch<'0'||ch>'9';ch=getchar()) if (ch=='-') f=-1;
	for (;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
	return x*f;
}
struct node {int a,b,c,id,f,ans;} a[N],b[N],t[N];
int n,m,n0,sum[N],ans[N],cnt[N];
bool operator<(node a,node b) {
	return a.a==b.a?(a.b==b.b?a.c<b.c:a.b<b.b):a.a<b.a;
}
int lowbit(int x) {return x&-x;}
void update(int x,int k) {for (;x<=m;x+=lowbit(x)) sum[x]+=k;}
int query(int x) {
	int ret=0; for (;x;x-=lowbit(x)) ret+=sum[x]; return ret;
}
void cdq(int l,int r) {
	if (l==r) return;
	int mid=(l+r)>>1;
	cdq(l,mid),cdq(mid+1,r);
	int i=l,j=mid+1,k=l;
	while (i<=mid&&j<=r) {
		if (a[i].b<=a[j].b) update(a[i].c,a[i].f),t[k++]=a[i++];
		else a[j].ans+=query(a[j].c),t[k++]=a[j++];
	}
	while (i<=mid) update(a[i].c,a[i].f),t[k++]=a[i++];
	while (j<=r) a[j].ans+=query(a[j].c),t[k++]=a[j++];
	for (int _=l;_<=mid;_++) update(a[_].c,-a[_].f);
	for (int _=l;_<=r;_++) a[_]=t[_];
}
int main() {
	n=read(),m=read();
	for (int i=1;i<=n;i++) {
		int x=read(),y=read(),z=read();
		b[i]=(node){x,y,z,0,0,0};
	}
	sort(b+1,b+n+1);
	for (int i=1,t=0;i<=n;i++) {
		++t;
		if (b[i].a!=b[i+1].a||b[i].b!=b[i+1].b||b[i].c!=b[i+1].c) {
			a[++n0]=b[i],a[n0].id=n0,a[n0].f=t,t=0;
		}
	}
	cdq(1,n0);
	for (int i=1;i<=n0;i++) cnt[a[i].ans+a[i].f-1]+=a[i].f;
	for (int i=0;i<n;i++) printf("%d\n",cnt[i]);
	return 0;
}
```

### 二维树状数组 区间加 区间求和

```c++
#pragma once
#include<cstdio>
#define LL long long
#define R register int
const int N=2050;
int n,m,T,a,b,c,d,e,f;LL C[N][N][4];
inline void in(int &x){
    x=f=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;
}
void add(int x,int y,int z){
    R i=x,j;
    while(i<=n){
        j=y;
        while(j<=m)C[i][j][0]+=z,C[i][j][1]+=z*x,C[i][j][2]+=z*y,C[i][j][3]+=z*x*y,j+=j&(-j);
        i+=i&(-i);
    }
}
LL ask_matrix(int x,int y){
    LL ans=0;
    R i=x,j;
    while(i){
        j=y;
        while(j)ans+=(x+1)*(y+1)*C[i][j][0]-(y+1)*C[i][j][1]-(x+1)*C[i][j][2]+C[i][j][3],j-=j&(-j);
        i-=i&(-i);
    }
    return ans;
}
int main(){
    in(n),in(m);
    while(scanf("%d",&a)>0){
        in(b),in(c),in(d),in(e);
        if(a==1)in(a),add(b,c,a),add(b,e+1,-a),add(d+1,c,-a),add(d+1,e+1,a);
        else --b,--c,printf("%lld\n",ask_matrix(d,e)-ask_matrix(d,c)-ask_matrix(b,e)+ask_matrix(b,c));
    }
}
```

### 维护全序集

插入 删除 k小 排名 前驱 后继

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace std;
char ch = 0;
char buf[20 << 20], *Now = buf, *End;
char wb[20 << 20], *ptr = wb;
struct IO {
    IO() {
        End = buf + fread(buf, 1, 20 << 20, stdin);
        cerr << "read complete" << endl;
    }
    ~IO() { fwrite(wb, 1, ptr - wb, stdout); }
} I_O;

#define getchar() (*Now++)

inline void read(int &a) {
    a = 0;
    while (ch < '0') ch = getchar();
    while (ch >= '0') a = a * 10 + ch - '0', ch = getchar();
}

#define putchar(x) (*ptr++ = x)

inline void pr(int x) {
    static char sta[11];
    int top = 0, tmp;
    if (x < 1) {
        if (x)
            putchar('-'), putchar('1');
        else
            putchar('0');
    } else {
        while (x) {
            tmp = x / 10;
            sta[++top] = char('0' + x - tmp * 10);
            x = tmp;
        }
        while (top) putchar(sta[top--]);
    }
    putchar('\n');
}

#define MAXN 300005
struct data {
    int x, p;
    inline bool operator<(const data &a) const { return x < a.x; }
} tem[MAXN];

int n, cnt, tot = 2, Log, rev[MAXN], opt[MAXN], num[MAXN];
int t[MAXN];

#define insert(y)                                      \
    {                                                  \
        for (int x = y; x <= tot; x += x & -x) ++t[x]; \
    }
#define del(y)                                         \
    {                                                  \
        for (int x = y; x <= tot; x += x & -x) --t[x]; \
    }

inline int rk(int x) {
    int ret = 1;
    for (--x; x; x -= x & -x) ret += t[x];
    return ret;
}

inline int get_rk(int k) {
    int ret = 0;
    for (int j = 1 << Log, to; j; j >>= 1) {
        to = ret | j;
        if (to <= tot && k > t[to])
            k -= t[ret = to];
    }
    return rev[ret + 1];
}

#define pre(x) get_rk(rk(x) - 1)
#define nxt(x) get_rk(rk(x))

int main() {
    read(n);
    for (int i = 1; i <= n; i++) {
        read(opt[i]);
        read(num[i]);
        if (opt[i] == 5)
            num[i]++;
        if (opt[i] != 2) {
            tem[++cnt].x = num[i];
            tem[cnt].p = i;
        }
    }
    sort(tem + 1, tem + cnt + 1);
    num[tem[1].p] = 2;
    rev[2] = tem[1].x;
    for (int i = 2; i <= cnt; i++) {
        if (tem[i].x != tem[i - 1].x) {
            num[tem[i].p] = ++tot;
            rev[tot] = tem[i].x;
        } else
            num[tem[i].p] = tot;
    }
    rev[tot + 1] = rev[1] = -1;
    for (Log = 0; tot >> Log; Log++)
        ;
    Log--;
    for (int i = 1; i <= n; i++) {
        switch (opt[i]) {
            case 0:
                insert(num[i]);
                break;
            case 1:
                del(num[i]);
                break;
            case 3:
                pr(rk(num[i]) - 1);
                break;
            case 2:
                pr(get_rk(num[i]));
                break;
            case 4:
                pr(pre(num[i]));
                break;
            case 5:
                pr(nxt(num[i]));
                break;
        }
    }
    return 0;
}
```



## 树上问题

### 树链剖分

换根

路径加值

子树加值

路径求和

子树求和

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#define ll long long
const int N = 101000;
int last[N],cnt;
int r,fa[N],n,m,d[N],size[N],ws[N],top[N],id[N],q[N],tot;
ll v[N],a[N];
ll sum[N][2];
struct edge{
	int next,to;
}e[N<<1];
void add(int x,ll v){
	for(int i=x;x<=n;x+=x&-x){
		sum[x][0]+=v,sum[x][1]+=v*i;
	}
}
ll ask(int x){
	ll ans=0;
	for(int i=x;x;x-=x&-x)
		ans+=sum[x][0]*(i+1)-sum[x][1];
	return ans;
}
void modify(int l,int r,ll v){
	add(l,v),add(r+1,-v);
}
ll query(int l,int r){
	return ask(r)-ask(l-1);
}
int read(){
	int x=0,fl=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')fl=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
	return x*fl;
}
void add(int a,int b){
	cnt++;e[cnt].next=last[a],last[a]=cnt;e[cnt].to=b;
}
void dfs(int x,int f){
	fa[x]=f,d[x]=d[f]+1;size[x]=1;
	for(int i=last[x];i;i=e[i].next){
		if(e[i].to==f) continue;
		dfs(e[i].to,x);
		if(size[e[i].to]>size[ws[x]])	ws[x]=e[i].to;
		size[x]+=size[e[i].to];
	}
}
void dfs2(int x,int topf){
	top[x]=topf;id[x]=++tot;q[tot]=x;
	modify(id[x],id[x],a[x]);
	if(ws[x]) dfs2(ws[x],topf);
	for(int i=last[x];i;i=e[i].next){
		if(e[i].to==fa[x]||e[i].to==ws[x]) continue;
		dfs2(e[i].to,e[i].to);
	}
}
int get_lca(int x,int y){
	while(top[x]!=top[y]){
		if(d[top[x]]<d[top[y]]) std::swap(x,y);
		x=fa[top[x]];
	}
	return d[x]>d[y]?y:x;
}
void Tmodify(int x,int y,ll v){
	while(top[x]!=top[y]){
		if(d[top[x]]<d[top[y]]) std::swap(x,y);
		modify(id[top[x]],id[x],v);
		x=fa[top[x]];
	}
	if(id[x]>id[y]) std::swap(x,y);
	modify(id[x],id[y],v);
}
ll Task(int x,int y){
	ll ans=0;
	while(top[x]!=top[y]){
		if(d[top[x]]<d[top[y]]) std::swap(x,y);
		ans+=query(id[top[x]],id[x]);
		x=fa[top[x]];
	}
	if(id[x]>id[y]) std::swap(x,y);
	ans+=query(id[x],id[y]);
	return ans;
}
int get_top(int x,int dth){
	while(dth+1<d[top[x]]) x=fa[top[x]];
	return q[id[top[x]]-(d[top[x]]-dth-1)];
}
int main(){
	n=read();r=1;
	for(int i=1;i<=n;++i)
		a[i]=read();
	for(int i=2;i<=n;++i){
		int a=read();add(a,i);
	}
	m=read();
	dfs(r,0);
	dfs2(r,r);
	while(m--){
		int opt=read();
		if(opt==1){
			r=read();
		}
		if(opt==2){
			int l=read(),r=read(),v=read();
			Tmodify(l,r,v);
		}
		if(opt==3){
			int x=read();
			ll v=read();
			if(x==r){
				modify(id[1],id[1]+size[1]-1,v);
			}
			else if(r!=x&&id[x]<=id[r]&&id[r]<=id[x]+size[x]-1){
				int ss=get_top(r,d[x]);
				modify(id[1],id[1]+size[1]-1,v);
				modify(id[ss],id[ss]+size[ss]-1,-v);
			}
			else{
				modify(id[x],id[x]+size[x]-1,v);
			}
		}
		if(opt==4){
			int l=read(),r=read();
			ll ans=Task(l,r);
			printf("%lld\n",ans);
		}
		if(opt==5){
			int x=read();
			if(x==r){
				ll ans=query(id[1],id[1]+size[1]-1);
				printf("%lld\n",ans);
			}
			else
			if(id[x]<=id[r]&&id[r]<=id[x]+size[x]-1){
				ll ans=0;
				int ss=get_top(r,d[x]);
				ans+=query(id[1],id[1]+size[1]-1);
				ans-=query(id[ss],id[ss]+size[ss]-1);
				printf("%lld\n",ans);
			}
			else{
				ll ans=query(id[x],id[x]+size[x]-1);
				printf("%lld\n",ans);
			}
		}
	}
}
```

### 节点修改 子树权值和

```c++
#include<cstdio>

using int64=long long;
using uchar=unsigned char;

constexpr int Maxn(1000000);

namespace IOManager{
	constexpr int FILESZ(131072);
	char buf[FILESZ];
	const char*ibuf=buf,*tbuf=buf;

	struct IOManager{
		inline char gc()
			{return(ibuf==tbuf)&&(tbuf=(ibuf=buf)+fread(buf,1,FILESZ,stdin),ibuf==tbuf)?EOF:*ibuf++;}

		template<class _Tp>
			inline operator _Tp(){
				_Tp s=0u;char c=gc(),w=0;
				for(;c<48;c=gc())
					c==45&&(w=1);
				for(;c>47;c=gc())
					s=(_Tp)(s*10u+c-48u);
				return w?-s:s;
			}
	};
}IOManager::IOManager io;

struct Edge{
	int v;Edge*las;

	inline Edge* init(const int&to,Edge*const&ls)
		{return v=to,las=ls,this;}
}*las[Maxn+1];

inline void AddEdge(){
	static Edge pool[Maxn<<1],*alc=pool-1;
	const int u=io,v=io;
	las[u]=(++alc)->init(v,las[u]);
	las[v]=(++alc)->init(u,las[v]);
}

int idx,
	s[Maxn+1],
	t[Maxn+1],
	v[Maxn+1];
int64 bit[Maxn+1];

const int n=io;
inline void update(int i,const int&d){
	for(;i<=n;i+=i&-i)
		bit[i]+=d;
}
inline int64 sum(int i){
	int64 qs=0;
	for(;i;i-=i&-i)
		qs+=bit[i];
	return qs;
}

void calc(const int&now,const int&Fa){
	update(s[now]=++idx,v[now]);

	for(Edge*o=las[now];o;o=o->las)
		if(o->v!=Fa)
			calc(o->v,now);

	t[now]=idx;
}

int main(){
	int m=io;const int r=io;
	for(int i=1;i<=n;++i)
		v[i]=io;
	for(int i=1;i<n;++i)
		AddEdge();

	int a;
	for(calc(r,0);m;--m)
		if((int)io==1)
			a=io,update(s[a],(int)io);
		else
			a=io,printf("%lld\n",sum(t[a])-sum(s[a]-1));

	return 0;
}
```

### 子树加值 子树权值和

``` c++
#include <unistd.h>
#include <sys/mman.h>
#include <cctype>
#include <algorithm>
#include <utility>
#include <iostream>
int N;
typedef long long LL;
namespace fast {
char *inP = static_cast<char *>(mmap(0, 3 << 24, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0)) - 1;
class istream {
public:
    inline istream &operator>>(int &RHS) {
        RHS = 0;
        bool neg = 0;
        while (std::isspace(*++inP))
            ;
        if (*inP == '-')
            neg = 1, ++inP;
        do
            RHS = 10 * RHS + (*inP ^ 48);
        while (std::isdigit(*++inP));
        if (neg)
            RHS = -RHS;
        return *this;
    }
} in;
char pool[1 << 24], *outP = pool - 1;
class ostream {
public:
    inline ostream &operator<<(LL RHS) {
        if (RHS < 0)
            *++outP = '-', RHS = -RHS;
        char buf[13], *out = buf;
        do
            *out++ = RHS % 10 ^ 48;
        while (RHS /= 10);
        while (out > buf) *++outP = *--out;
        return *this;
    }
    inline ostream &operator<<(const char &RHS) {
        *++outP = RHS;
        return *this;
    }
    inline ~ostream() { std::cout.rdbuf()->sputn(pool, outP - pool + 1); }
} out;
}  // namespace fast
const int max = 1E6;
typedef int AI[max | 1];
AI v, idx;
std::pair<int, int> edge[max - 1 << 1 | 1];
inline void link(int u, int v) {
    static int cnt;
    edge[++cnt] = { v, idx[u] }, idx[u] = cnt;
}
AI in;
namespace BIT {
LL a[max | 1], b[max | 1];
inline void add(int pos, int val) {
    LL val_ = static_cast<LL>(val) * pos;
    while (pos <= N) {
        a[pos] += val, b[pos] += val_;
        pos += pos & -pos;
    }
}
inline LL query(int pos) {
    int pos_ = pos;
    LL resa = 0, resb = 0;
    while (pos) {
        resa += a[pos], resb += b[pos];
        pos &= pos - 1;
    }
    return (pos_ + 1) * resa - resb;
}
}  // namespace BIT
AI out;
void DFS(int cur, int fa) {
    static int clock;
    BIT::add(in[cur] = ++clock, v[cur]), BIT::add(clock + 1, -v[cur]);
    for (int i = idx[cur]; i; i = edge[i].second)
        if (edge[i].first != fa)
            DFS(edge[i].first, cur);
    out[cur] = clock;
}
main() {
    int M, R;
    fast::in >> N >> M >> R;
    std::for_each(v + 1, v + N + 1, [](int &v) { fast::in >> v; });
    for (int n = N; --n;) {
        int u, v;
        fast::in >> u >> v;
        link(u, v), link(v, u);
    }
    for (DFS(R, 0); M--;) {
        int op, a;
        fast::in >> op >> a;
        if (op == 1) {
            int x;
            fast::in >> x;
            BIT::add(in[a], x), BIT::add(out[a] + 1, -x);
        } else
            fast::out << BIT::query(out[a]) - BIT::query(in[a] - 1) << '\n';
    }
}
```



### 树上差分 路径加值 节点查询 子树权值和

```c++
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <algorithm>
#include <sys/mman.h>
#define N 1000010
#define LL long long
using namespace std;
struct buf {
    char* s;
    buf() : s((char*)mmap(0, 150000010, PROT_READ, MAP_PRIVATE, fileno(stdin), 0)) {}
    operator int() {
        int x = 0, y = 0;
        while (*s < 48)
            if (*s++ == 45)
                y = 1;
        while (*s > 32) x = x * 10 + *s++ - 48;
        return y ? -x : x;
    }
    //	operator int(){ int x; scanf("%d",&x); return x; }
} it;
struct ouf {
    char *s, *t, *r, *l;
    ouf() : s((char*)malloc(10000000)), r((char*)malloc(20)), t(s) {}
    ~ouf() { write(fileno(stdout), s, t - s); }
    inline void operator()(LL x) {
        if (x < 0)
            *t++ = 45, x = -x;
        if (!x)
            *t++ = 48;
        else {
            for (l = r; x; x /= 10) *++l = x % 10 | 48;
            for (; l != r; *t++ = *l--)
                ;
        }
        *t++ = '\n';
    }
} ot;
struct edge {
    int v, nt;
} G[N << 1];
int t, n, m, R, clk = 0, h[N], l[N], r[N], v[N], d[N];
int sz[N], top[N], son[N], f[N];
LL w[N], s[N], sd[N];
inline void dfs(const int& x, const int& p) {
    d[x] = d[p] + 1;
    sz[x] = 1;
    f[x] = p;
    for (int v, i = h[x]; i; i = G[i].nt)
        if (!d[v = G[i].v]) {
            dfs(v, x);
            sz[x] += sz[v];
            if (sz[v] > sz[son[x]])
                son[x] = v;
        }
}
inline void dgs(const int& x, const int& p) {
    l[x] = ++clk;
    top[x] = p;
    w[clk] = v[x];
    if (son[x])
        dgs(son[x], p);
    for (int v, i = h[x]; i; i = G[i].nt)
        if (!l[v = G[i].v])
            dgs(v, v);
    r[x] = clk;
}
inline void add(int y, LL v) {
    for (int x = l[y]; x <= n; x += x & -x) s[x] += v, sd[x] += v * d[y];
}
inline LL s1(int y, LL v = 0) {
    v = w[l[y]] - w[l[y] - 1];
    for (int x = l[y] - 1; x; x &= x - 1) v -= s[x];
    for (int x = r[y]; x; x &= x - 1) v += s[x];
    return v;
}
inline LL s2(int y, LL v = 0) {
    v = w[r[y]] - w[l[y] - 1];
    for (int x = l[y] - 1; x; x &= x - 1) v -= sd[x] - s[x] * (d[y] - 1);
    for (int x = r[y]; x; x &= x - 1) v += sd[x] - s[x] * (d[y] - 1);
    return v;
}
inline void lca(int& x, int& y) {
    for (; top[x] ^ top[y]; y = f[top[y]])
        if (d[top[x]] > d[top[y]])
            swap(x, y);
    if (d[x] > d[y])
        swap(x, y);
}
int main() {
    n = it, m = it;
    R = it;
    for (int i = 1; i <= n; ++i) v[i] = it;
    for (int x, y, i = 1; i < n; ++i) {
        x = it;
        y = it;
        G[++t] = (edge){ y, h[x] };
        h[x] = t;
        G[++t] = (edge){ x, h[y] };
        h[y] = t;
    }
    dfs(R, 0);
    dgs(R, R);
    for (int i = 1; i <= n; ++i) w[i] += w[i - 1];
    for (int o, x, y; m--;) {
        o = it;
        if (o == 1) {
            x = it;
            y = it;
            o = it;
            add(x, o);
            add(y, o);
            lca(x, y);
            add(x, -o);
            if (x ^ R)
                add(f[x], -o);
        } else if (o == 2)
            ot(s1(it));
        else
            ot(s2(it));
    }
}
```

### 单点加 子树加 路径求和

```c++
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <algorithm>
#include <sys/mman.h>
#define N 1000010
#define LL long long
using namespace std;
struct buf {
    char* s;
    buf() : s((char*)mmap(0, 150000010, PROT_READ, MAP_PRIVATE, fileno(stdin), 0)) {}
    operator int() {
        int x = 0, y = 0;
        while (*s < 48)
            if (*s++ == 45)
                y = 1;
        while (*s > 32) x = x * 10 + *s++ - 48;
        return y ? -x : x;
    }
    //	operator int(){ int x; scanf("%d",&x); return x; }
} it;
struct ouf {
    char *s, *t, *r, *l;
    ouf() : s((char*)malloc(10000000)), r((char*)malloc(20)), t(s) {}
    ~ouf() { write(fileno(stdout), s, t - s); }
    inline void operator()(LL x) {
        if (x < 0)
            *t++ = 45, x = -x;
        if (!x)
            *t++ = 48;
        else {
            for (l = r; x; x /= 10) *++l = x % 10 | 48;
            for (; l != r; *t++ = *l--)
                ;
        }
        *t++ = '\n';
    }
} ot;
struct edge {
    int v, nt;
} G[N << 1];
int t, n, m, R, clk = 0, h[N], l[N], r[N], v[N], d[N];
int sz[N], top[N], son[N], f[N];
LL w[N], s[N], sd[N];
inline void dfs(const int& x, const int& p) {
    d[x] = d[p] + 1;
    sz[x] = 1;
    f[x] = p;
    for (int v, i = h[x]; i; i = G[i].nt)
        if (!d[v = G[i].v]) {
            dfs(v, x);
            sz[x] += sz[v];
            if (sz[v] > sz[son[x]])
                son[x] = v;
        }
}
inline void dgs(const int& x, const int& p) {
    l[x] = ++clk;
    top[x] = p;
    w[x] = w[f[x]] + v[x];
    if (son[x])
        dgs(son[x], p);
    for (int v, i = h[x]; i; i = G[i].nt)
        if (!l[v = G[i].v])
            dgs(v, v);
    r[x] = clk;
}
inline void F1(int v, int y) {
    for (int x = l[y]; x <= n; x += x & -x) s[x] += v;
    for (int x = r[y] + 1; x <= n; x += x & -x) s[x] -= v;
}
inline void F2(LL v, int y) {
    for (int x = l[y]; x <= n; x += x & -x) sd[x] += v, s[x] -= v * (d[y] - 1);
    for (int x = r[y] + 1; x <= n; x += x & -x) sd[x] -= v, s[x] += v * (d[y] - 1);
}
inline LL F(int y, LL v = 0) {
    v = w[y];
    for (int x = l[y]; x; x &= x - 1) v += d[y] * sd[x] + s[x];
    return v;
}
inline int lca(int x, int y) {
    for (; top[x] ^ top[y]; y = f[top[y]])
        if (d[top[x]] > d[top[y]])
            swap(x, y);
    if (d[x] > d[y])
        swap(x, y);
    return x;
}
int main() {
    n = it, m = it;
    R = it;
    for (int i = 1; i <= n; ++i) v[i] = it;
    for (int x, y, i = 1; i < n; ++i) {
        x = it;
        y = it;
        G[++t] = (edge){ y, h[x] };
        h[x] = t;
        G[++t] = (edge){ x, h[y] };
        h[y] = t;
    }
    dfs(R, 0);
    dgs(R, R);
    for (int o, x, y; m--;) {
        o = it;
        if (o == 1)
            F1(it, it);
        else if (o == 2)
            F2(it, it);
        else {
            x = it;
            y = it;
            o = lca(x, y);
            ot(F(x) + F(y) - F(o) - F(f[o]));
        }
    }
}
```



## 数学 

### 多项式乘法

``` c++
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define REP(i,n) for(int i=(0);i<(n);i++)
using namespace std;
typedef vector<int> poly;
typedef unsigned long long ll;

inline int read(){
	char ch=getchar();int x=0,op=0;
	while(!isdigit(ch))op|=(ch=='-'),ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return op?-x:x;
}

const int mod=998244353;
namespace Poly{
	const int N=(1<<20)+5,g=3;
	inline int power(int x,int p){
		int res=1;
		for(;p;p>>=1,x=(ll)x*x%mod)
			if(p&1)res=(ll)res*x%mod;
		return res;
	}
	void dft(poly &A,int n){
		static ll W[N<<1],*H[30],*las=W,mx=0;
		for(;mx<n;mx++){
			H[mx]=las;ll w=1,wn=power(g,(mod-1)>>(mx+1));
			REP(i,1<<mx)*las++=w,w=w*wn%mod;
		}
		static ll a[N];A.resize(1<<n);
		for(int i=0,j=0;i<(1<<n);++i){
			a[i]=A[j];
			for(int k=1<<(n-1);(j^=k)<k;k>>=1);
		}
		for(int k=0,d=1;k<n;k++,d<<=1)
			for(int i=0;i<(1<<n);i+=d<<1){
				ll *l=a+i,*r=a+i+d,*w=H[k],t;
				for(int j=0;j<d;++j,++l,++r){
					t=(*w++)*(*r)%mod;
					*r=*l+mod-t,*l+=t;
				}
			}
		REP(i,1<<n)A[i]=a[i]%mod;
	}
	void idft(poly &a,int n){
		a.resize(1<<n);
		reverse(a.begin()+1,a.end());
		dft(a,n);
		int inv=power(1<<n,mod-2);
		REP(i,1<<n)a[i]=(ll)a[i]*inv%mod;
	}
	poly mul(poly a,poly b){
		int aim=(a.size()+b.size()),n=1;
		while((1<<n)<=aim)n++;
		dft(a,n),dft(b,n);
		REP(i,1<<n)a[i]=(ll)a[i]*b[i]%mod;
		return idft(a,n),a.resize(aim),a;
	}
}


struct fio{char a[1<<25],*s;char b[1<<25],*t;
fio():s(a),t(b){a[fread(a,1,sizeof a,stdin)]=0;}
~fio(){fwrite(b,1,t-b,stdout);}
inline int ii(){int x=0;while(*s<48)++s;
while(*s>32)x=x*10+*s++-48;return x;}
inline ll il(){ll x=0;while(*s<48)++s;
while(*s>32)x=x*10+*s++-48;return x;}
inline int sp(){while(*s<48)++s;return*s++-48;}
inline void out(int x, char e=' ')
{static char c[12];char*i=c;if(!x)*t++=48;
else{while(x){int y=x/10;*i++=x-y*10+48,x=y;}
while(i!=c)*t++=*--i;}*t++=e;}}io;

int main(){
	int n=io.ii()+1,m=io.ii()+1;
	poly A(n,0),B(m,0);
	REP(i,n)A[i]=io.ii();
	REP(i,m)B[i]=io.ii();
	poly C=Poly::mul(A,B);
	REP(i,n+m-1)io.out(C[i]);
	return 0;
}
```



### 矩阵乘法

```c++
#include <cstdio>

#define R register
#define Get() (Ch = getchar())
#define IsN (Ch >= '0' && Ch <= '9')
inline int Fastin() {
	R int N = 0; R char Ch; R bool Bo = 0;
	for(Get(); !IsN && Ch != '-'; Get()); 
	Ch == '-'? Bo = 1: N = Ch - '0';
	for(Get(); IsN; Get()) N = (N << 3) + (N << 1) + Ch - '0';
	return Bo? -N: N;
}

#define Mod 1000000007
int N, P, M; 
long long A[510][510], B[510][510], C[510][510];

int main(void) {
	N = Fastin(), P = Fastin(), M = Fastin();
	for(R int i = 1; i <= N; ++i) {
		for(R int j = 1; j <= P; ++j) A[i][j] = Fastin() % Mod;
	}
	for(R int i = 1; i <= P; ++i) {
		for(R int j = 1; j <= M; ++j) B[i][j] = Fastin() % Mod;
	}
	for(R int i = 1; i <= N; ++i) {
		for(R int k = 1; k <= P; ++k) {
			if(A[i][k]) {
				for(R int j = 1; j <= M; ++j) C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % Mod;
			}
		}
	}
	for(R int i = 1; i <= N; ++i) {
		for(R int j = 1; j <= M; ++j) printf("%lld ", C[i][j] < 0? C[i][j] + Mod: C[i][j]); puts("");
	}
	return 0;
} 
```

### 米勒罗宾判断质数

```c++
#include <bits/stdc++.h>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
typedef long long ll;
inline int read() {
	int f=1,sum=0;
	char x=getchar();
	for(;(x<'0'||x>'9');x=getchar()) if(x=='-') f=-1;
	for(;x>='0'&&x<='9';x=getchar()) sum=sum*10+x-'0';
	return f*sum;
}

int x_[10]={3,5,7,11,13,17,19,23};


inline ll mul(ll x,ll y,ll mod) {
	ll tmp=x*y-((ll)((long double)x/mod*y+0.5))*mod;
	return tmp<0?tmp+mod:tmp;
}

inline ll qmul(ll x,ll ci,ll mod) {
	ll sum=1;
	for(;ci;ci>>=1,x=mul(x,x,mod))
		if(ci&1) sum=mul(sum,x,mod);
	return sum;
}

inline bool Miller_Rabin(ll n) {
	if(n==1) return 0;
	if(n==2) return 1;
	if(!(n&1)) return 0;
	ll t=n-1;
	int now=0;
	while (!(t&1)) t>>=1,++now;
	
	for(int i = 0; i <= 7; i++){
		if(x_[i]==n) return 1;
		ll x=qmul(x_[i],t,n),y=x;
		for(int j = 1; j <= now; j++) {
			x=mul(x,x,n);
			if(x==1&&!(y==1||y==n-1)) return 0;
			y=x;
		}
		if(x!=1) return 0;
	}
	return 1;
}

int main () {
	//freopen("a.in","r",stdin);
	ll x;
	while (scanf("%lld",&x)==1) {
		if(Miller_Rabin(x)) puts("Y");
		else puts("N");
	}
}
```



## 其他

### 最大异或和

```c++
#include<bits/stdc++.h>
using namespace std;
long long n,a[100],f[100],ans;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++)cin>>a[i];
	for (int i=1;i<=n;i++)
		for (int j=50;j>=0;j--)
			if (a[i]&(1ll<<j))
				{
					if (f[j])a[i]^=f[j];
						else {f[j]^=a[i];break;}
				}
	for (int i=50;i>=0;i--)
		if ((ans^f[i])>ans)ans^=f[i];
	cout<<ans<<endl;
}
```

### k 大异或和

```c++
#include <cstdio>
#include <cstring>

typedef long long lnt;
const int mxn = 55;
int n, m, cnt;
lnt b[mxn];
lnt c[mxn];

signed main() {
	scanf("%d", &n);	
	for (int i = 1; i <= n; ++i) {
		lnt x; scanf("%lld", &x);		
		for (int j = 51; ~j; --j)
			if ((x >> j) & 1) {
				if (!b[j]) {
					b[j] = x;
					break;
				}
				else
					x ^= b[j];
			}
	}	
	for (int i = 0; i <= 51; ++i)
		for (int j = i + 1; j <= 51; ++j)
			if ((b[j] >> i) & 1)
				b[j] ^= b[i];
	for (int i = 0; i <= 51; ++i)
		if (b[i])c[cnt++] = b[i];	
	scanf("%d", &m);	
	for (int i = 1; i <= m; ++i) {
		lnt x, y = 0; scanf("%lld", &x);		
		if (cnt != n)--x;	 // zero		
		if (x > (1LL << cnt) - 1)
			puts("-1");
		else {
			for (int j = 0; j < cnt; ++j)
				if ((x >> j) & 1)
					y ^= c[j];
			printf("%lld\n", y);
		}
	}
}
```

### 0/1分数规划

最大化 sum ai*xi / sum bi * xi

```c++
#include<cstdio>
#include<algorithm>
#include<ctype.h>
#include<string.h>
#include<math.h>

using namespace std;
#define ll long long

inline char read() {
	static const int IN_LEN = 1000000;
	static char buf[IN_LEN], *s, *t;
	return (s==t?t=(s=buf)+fread(buf,1,IN_LEN,stdin),(s==t?-1:*s++):*s++);
}
template<class T>
inline void read(T &x) {
	static bool iosig;
	static char c;
	for (iosig=false, c=read(); !isdigit(c); c=read()) {
		if (c == '-') iosig=true;
		if (c == -1) return;
	}
	for (x=0; isdigit(c); c=read()) x=((x+(x<<2))<<1)+(c^'0');
	if (iosig) x=-x;
}

const int N = 100005;
int n, k;
struct item{
	int a, b;
	double f;
	inline bool operator <(const item &rhs)const{ return f>rhs.f;}
} a[N];
inline double check(double x){
	for(int i=1; i<=n; ++i) a[i].f=a[i].a-a[i].b*x;
	nth_element(a+1, a+k+1, a+n+1);
	ll sa=0, sb=0;
	for(int i=1; i<=k; ++i) sa+=a[i].a, sb+=a[i].b;
	return (double)sa/sb;
}
int main() {
	read(n), read(k);
	for(int i=1; i<=n; ++i) read(a[i].a);
	for(int i=1; i<=n; ++i) read(a[i].b);
	ll sa=0, sb=0;
	for(int i=1; i<=k; ++i) sa+=a[i].a, sb+=a[i].b;
	double ans=(double)sa/sb, last;
	do ans=check(last=ans); while(ans-last>1e-6);
	return printf("%.4f", ans), 0;
}
```

