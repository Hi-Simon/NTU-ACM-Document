//#include <iostream>
//#include <random>

std::vector<int> permutation(100);
for (int i = 0; i < 100; i++) {
	permutation[i] = i+1;
}
std::mt19937_64 mt1(1); //64位
std::mt19937 mt2(2); //32位
shuffle(permutation.begin(), permutation.end(), mt2); // 打乱序列
for (auto it: permutation) {
	std::cout << it << " ";
}