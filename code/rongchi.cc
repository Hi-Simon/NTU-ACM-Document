/*
 * Author: Simon
 * 复杂度: O(2^k+sqrt(n))其中k为n中不同的质因数的个数，n<=10^5时，k最大为5
 * 功能: 容斥求[1,n]中与p互质的数的和
 */ 
/*求n的质因数*/
void solve(int n){ /*需预处理欧拉筛*/
	fac.clear();
	for(int i=1;i<=cnt&&prime[i]*prime[i]<=n;i++){
		if(n%prime[i]==0){
			fac.push_back(prime[i]);
			while(n%prime[i]==0) n/=prime[i];
		}
	}
	if(n>1) fac.push_back(n);
}
/*求和公式*/
int sum_1(int n){
	return n*(n+1)/2;
}
/*容斥求[1,n]中与p互质的数的和*/
int cal(int n,int p){
	solve(p); /*求出p的质因数*/
	int ans=0;
	for(int i=1;i<(1<<fac.size());i++){ /*枚举子集*/
		int num=0,lcm=1;
		for(int j=0;j<fac.size();j++){
			if(i>>j&1){
				num++;lcm*=fac[j];	
			}
		}
		if(num&1) ans+=sum_1(n)-sum_1(n/lcm)*lcm; /*总和减去不互质的数的和*/
		else ans-=sum_1(n)-sum_1(n/lcm)*lcm;
	}
	return ans;
}