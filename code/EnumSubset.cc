void print_subset(int n, int s) {
	for (int i = 0; i < n; i++) {
		if (s & (1 << i)) {
			std::cout << i << " ";
		}
		std::cout << '\n';
	}
}
int main(int argc, char *argv[]) {
	int n;
	std::cin >> n;
	for (int i = 0; i < (1 << n); i++) print_subset(n, i);
}

//当x代表集合 x的子集: for (int i = x; i; i=(i-1)&x) {}