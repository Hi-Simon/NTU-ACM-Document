d[1] = 0;
d[2] = 1;
for (int i = 3; i < maxn; i++) {
	d[i] = (i-1)*(d[i-1]+d[i-2]);
}