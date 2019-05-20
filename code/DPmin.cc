//单调队列求区间最小值
int a[maxn], q[maxn], num[maxn] = {0};
int Fmin[maxn];
int k, n, head, tail;

void DPmin() {
	head = 1, tail = 0;
	for (int i = 1; i <= n; i++) {
		while (num[head] < i-k+1 && head <= tail) head++;
		while (a[i] <= q[tail] /*区间最大值此处改为>=*/ && head <= tail) tail--;
		num[++tail] = i; 
		q[tail] = a[i];
		Fmin[i] = q[head];
	}
}