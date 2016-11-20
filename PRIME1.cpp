#include <iostream>
#include <new>
#include <cmath>
#include <ctime>
#include <vector>

static const size_t upper = 32000;

static void eratos(std::vector<size_t>& primes) {
	bool *arr = new bool[upper];
	for (size_t i = 2 ; i < upper ; i++)
		arr[i] = true;

	for (size_t i = 2 , j; i*i < upper ; i++) {
		if (arr[i]) {
			for (j = i*i; j < upper ; j += i)
				arr[j] = false;
		}
	}

	for (size_t i = 2 ; i < upper ; i++)
		if (arr[i]) primes.push_back(i);

	delete[] arr;
}

// static void atkin(std::vector<size_t>& res) {
// 	bool *arr = new bool[upper];
// 	for (size_t i = 0 ; i < upper ; i++)
// 		arr[i] = false;
//
// 	size_t x,y,n;
// 	for (x = 1; x*x < upper; x++) {
// 		for (y = 1; y*y < upper; y++) {
// 			n = 4*x*x + y*y;
// 			if (n < upper && n % 4 == 1)
// 				arr[n] ^= true;
//
// 			n -= x*x;
// 			if (n < upper && n % 6 == 1)
// 				arr[n] ^= true;
//
// 			n -= 2*y*y;
// 			if (x > y && n < upper && n % 12 == 11)
// 				arr[n] ^= true;
// 		}
// 	}
// 	for (n = 5; n*n < upper; n++) {
// 		if (arr[n]) {
// 			for (x = n*n; x < upper; x += n*n)
// 				arr[x] = false;
// 		}
// 	}
//
// 	if (upper >= 2) res.push_back(2);
// 	if (upper >= 3) res.push_back(3);
//
// 	for (x = 5; x < upper; x++)
// 		if (arr[x]) res.push_back(x);
//
// 	delete[] arr;
// }

int main() {

	// primes < sqrt(1E9) ~ 32k
	std::vector<size_t> primes(2919);
	primes.clear();

	eratos(primes);

	int t, m , n;
	std::cin >> t;
	std::vector<bool> ans;
	while (t-->0) {
		std::cin >> m >> n;
		ans.resize(n-m+1, true);
		for (size_t i = 0; i < ans.size() ; i++) {
			if (!ans[i]) continue;
			for (auto& p : primes) {
				if ((i+m) % p == 0 && (i+m) != p) {
					for (size_t j = i; j < ans.size(); j += p)
						ans[j] = false;
					break;
				}
			}
			if (ans[i] && i+m != 1)
				std::cout << i+m << std::endl;
		}
		if (t != 0) std::cout << std::endl;
	}

	return 0;
}
