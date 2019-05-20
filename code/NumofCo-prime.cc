//Written by Simon
//求r以内与n不互质的数的个数
int solve(int r) {
	int sum=0;
	for(int i=1;i<(1<<fac.size());i++) {//枚举质因数的每一种组合
		int ans=1,num=0;
		for(int j=0;j<fac.size();j++) {//求当前组和的积
			if(i&(1<<j)) {
				ans *= fac[j];
				num++;
			}
		}
		if(num&1) sum+=r/ans;//如果当前组合个数为奇数个，加上r以内能被ans整除的数的个数
		else sum-=r/ans;//否则减去r以内能被ans整除的数的个数
	}
	return sum;
}