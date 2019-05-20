//Author:CookiC
//返回下标最大的匹配串
#include <cstring>

void getFail(char *P, int *f) {
	int i, j;
	f[0] = 0;
	f[1] = 0;
	for(i=1; P[i]; ++i) {
		j = f[i];
		while(j && P[i]!=P[j]) {
			j = f[j];
		}
		f[i+1] = P[i]==P[j]? j+1: 0;
	}
}

int kmp(char *T, char *P) {
	int ans = -1;
	int n = strlen(T), m = strlen(P);
	int f[maxn];
	getFail(P, f);
	int j = 0;
	for(int i=0; i<n; ++i){
		while(j && P[j]!=T[i])
		j = f[j];
		if(P[j]==T[i]) {
			++j;
		}
		if(j==m) {
			j = f[j];
			ans = i-m+1;
		}
	}
	return ans;
}