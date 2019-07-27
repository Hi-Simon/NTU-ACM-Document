//#define inf maxn*maxw+10
for(int i = 0; i < n; i++) {
	for(int j = 0; j < n; j++) {
		d[i][j] = inf;
	}
}
d[0][0] = 0;
for(int k = 0; k < n; k++) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);		
		}
	}
}
/*
 * Author: Simon
 * 功能: 传递闭包
 */
for(int k=1;k<=n;k++){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i][k]&&a[k][j]) a[i][j]=1;  /*传递闭包 */
        }
    }
}