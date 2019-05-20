using ll = long long;
int n, MAX_BASE;
ll a[maxn], b[maxn];

void cal() {
	for (int i=1; i<=n; i++) for(int j=MAX_BASE; j>=0; j--) {
		if ((a[i]>>j)&1) {
			if(b[j]) a[i]^=b[j];
			else {
				b[j] = a[i];
				for (int k=j-1; k>=0; k--)			 if (b[k]&&((b[j]>>k)&1)) 	b[j] ^= b[k];
				for (int k=j+1; k<=MAX_BASE; k++)	 if ((b[k]>>j)&1) 			b[k] ^= b[j];
				break;
			}
		}
	}
}