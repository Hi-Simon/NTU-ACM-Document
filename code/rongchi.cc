for(int i=0;i<fac.size();i++){ //容斥求 [0,m)内，a1,a2...ak的倍数的和，每个数只记一次
	if(vis[i]==num[i]) continue;// vis数组为 fac[i]这个数要用几次，这里vis[i]=1
	int n=(m-1)/fac[i];
	ans+=(1+n)*n/2*fac[i]*(vis[i]-num[i]);// num[i]数组为 fac[i]这个数已经用了几次，多了就要减去多用的次数
	n=vis[i]-num[i];         //用于更新已经用的次数
	for(int j=i;j<fac.size();j++){
		if(fac[j]%fac[i]==0){
			num[j]+=n; //在此题中 将所有fac[i]的倍数 更新已使用次数
		}
	}
}