#include <cstdio>
#include <cmath>
#define type int

type c[mm], in[mn], w[mn], ans;
int s[mm], t[mm], id[mn], pre[mn], q[mn], vis[mn];

type Directed_MST(int root,int NV,int NE) {
	type ret=0, sum=0, tmp;
	int i, j, u, v, r;
	bool huan=1;
	for (i=0;i<=NV;++i) in[i]=0, id[i]=i, pre[i]=-1;
	while (huan) {
		for(i=0;i<=NV;++i)
			if(pre[j=id[i]]>=0) {
				if(pre[i]<0)in[i]+=w[j],id[i]=id[j];
				else in[i]+=w[i],ret+=w[i];
			}
		for(i=0;i<=NV;++i)pre[i]=-1,vis[i]=0;
		for(i=0;i<NE;++i)
			if((u=id[s[i]])!=(v=id[t[i]])&&(w[v]>(tmp=c[i]-in[t[i]])||pre[v]<0))
				pre[v]=u,w[v]=tmp;
		for(i=1;i<=NV;++i)
			if(i!=root&&id[i]==i&&pre[i]<0)return -1;
		for(pre[root]=-1,sum=i=0;i<=NV;++i)
			if(pre[i]>=0)sum+=w[i];
		for(i=huan=0;i<=NV;++i)
			if(!vis[i]) {
				r=0,j=i;
				while(j>=0&&vis[j]>=0) {
					if(vis[j]>0) {
						while(q[--r]!=j)id[q[r]]=j,vis[q[r]]=-1;
						huan=1,vis[j]=-1;
					}
					else vis[q[r++]=j]=1,j=pre[j];
				}
				while(r--)vis[q[r]]=pre[q[r]]=-1;
			}
	}
	return ret+sum;
}

int main() {
	int n,m,e,T,cas=0;
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m),--n;
		e=0;
		while(m--)scanf("%d%d%d",&s[e],&t[e],&c[e]),e+=(s[e]!=t[e]);
		ans=Directed_MST(0,n,e);
		if(ans<0)printf("Case #%d: Possums!\n",++cas);
		else printf("Case #%d: %d\n",++cas,ans);
	}
	return 0;
}