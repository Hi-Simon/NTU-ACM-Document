//树状数组求逆序对
const int maxn = "Edit";

int lowbit(int x) {
	return (x&-x);
}

bool cmp(std::pair<int, int> no1, std::pair<int, int> no2) {
	return no1.first < no2.first;
}

int d[maxn], p[maxn], n;
std::pair<int, int> start[maxn];

void add(int x) {
	while (x <= n) {
		d[x]++;
		x += lowbit(x);
	}
}

long long sum(int x) {
	long long sum = 0;
	while (x) {
		sum += d[x];
		x -= lowbit(x);
	}
	return sum;
}

int main(int argc, char *argv[]) {
	long long ans;
	std::cin>>n;
	memset(d,0,sizeof(d));
	ans=0;
	for (int i=1;i<=n;i++) {
		std::cin >> start[i].first;
		start[i].second = i;
	}
	std::sort(start+1, start+n+1, cmp);
	int id = 1;
	p[start[1].second]=1;
	for (int i = 2; i <= n; ++i) {
		if (start[i].first == start[i-1].first) {
			p[start[i].second] = id;
		} else {
			p[start[i].second] = ++id;
		}
	}
	for (int i=1;i<=n;i++) {
	   add(p[i]);
	   ans += i - sum(p[i]);
	}
	std::cout << ans << std::endl;
	return 0;
}