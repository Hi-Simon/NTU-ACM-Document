int prime[maxn],mu[maxn],cnt=0;
bool vis[maxn];
void Mobius(int n){
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=cnt && prime[j]*i<=n;j++){
			vis[prime[j]*i]=1;
			if(i%prime[j]==0) break;
			mu[i*prime[j]]=-mu[i];
		}
	}
}