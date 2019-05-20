//数组离散化 含重复元素
std::sort(sub_a, sub_a+n);
int size = std::unique(sub_a, sub_a+n) - sub_a;//size为离散化后元素个数
for (i = 0; i < n; i++) {
	a[i] = std::lower_bound(sub_a, sub_a+size, a[i]) - sub_a + 1;//k为b[i]经离散化后对应的值
}

//坐标离散化
int compress(int *x1, int *x2, int w){
	std::vector<int> xs;
	for (int i = 0; i < N; i++) {
	  for (int d = -1; d <= 1; d++) {
		  int tx1 = x1[i] + d, tx2 = x2[i] + d;
		  if (1 <= tx1 && tx1 <= w) xs.push_back(tx1);
		  if (1 <= tx2 && tx2 <= w) xs.push_back(tx2);
	  }
	}
	std::sort(xs.begin(), xs.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());
	for (int i = 0; i < N; i++) {
	  x1[i] = find(xs.begin(), xs.end(), x1[i]) - xs.begin();
	  x2[i] = find(xs.begin(), xs.end(), x2[i]) - xs.begin();
	}
	return xs.size();
}