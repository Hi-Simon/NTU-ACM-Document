int DuJiao(int n)// 杜教筛--欧拉函数之和
{
	if(n<maxn) return Phi[n]; //欧拉函数前缀和
	if(mp[n]!=-1) return mp[n];
	int sum=0,z=n%mod;
	// for(int l=2,r;l<=n;l=r+1) // #version 1
	// {
	//     r=n/(n/l);
	//     sum+=DuJiao(n/l)*(r-l+1);
	//     sum%=mod;
	// }
	for(int i=1;i*i<=n;i++) // #vsesion 2-----对每一个i=[2...n]求sum[phi(1)+...+phi(n/i)]    
	{
		sum+=DuJiao(i)*(n/i-n/(i+1)); 
		sum%=mod;
		int x=n/i; //x为值，枚举i求x;
		if(x==i||i==1) continue;
		sum+=DuJiao(x)*(n/x-n/(x+1));
		sum%=mod;
	}
	sum=((z*(z+1)%mod*inv2%mod)%mod-sum%mod+mod)%mod; //等差数列前n项和-sum
	mp.insert(n,sum);//加入HashMap
	return sum%mod;
}