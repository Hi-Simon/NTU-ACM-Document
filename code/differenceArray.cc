//Author:CookiC
/*
*a为原数组
*C为差分数组
*/
int a[]={0, 1, 1, 1, 1, 1, 1};
int N, C[maxn];

int Sum(unsigned n) {
	int sum = 0;
	while(n>0){
		sum += C[n];
		n -= lowbit(n);
	}
	return sum;
}

void Add(unsigned n, int d) {
	while(n<=N){
		C[n]+=d;
		n+=lowbit(n);
	}
}

void Add(int L,int R, int d) {
	Add(L,d);
	Add(R+1,-d);
}

void Init() {
	memset(C, 0, sizeof(C));
	Add(1, a[1]);
	for(int i=2; i<=N; ++i)
		Add(i, a[i]-a[i-1]);
}

void Update() {
	for(int i=1; i<=N; ++i)
		a[i] = Sum(i);
}