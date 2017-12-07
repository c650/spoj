#include <bits/stdc++.h>

#define BOOP (sizeof(long) * 8)

/* [last_bit][k] */
long dp[2][BOOP+1];

static long go(const int& k, const bool& eq, const std::string& bound, const int& sum, const int& last_bit) {

	// std::printf("k = %d. sum = %d\n", k, sum);

	if (k >= bound.length()) {
		return sum == 4 || sum == 7 || sum == 44 || sum == 47;
	}

	// if (dp[eq][k] != -1)
	// 	return dp[eq][k];

	int top = eq ? bound.at(k) - '0' : 1;
	// std::printf("top  = %d\n", top);

	long cnt = 0;
	for (int i = 0; i <= top; ++i) {

		cnt += go(k+1, eq && i == top, bound, sum + i, i);
	}

	if (!eq) return dp[eq][k] = cnt;
	else return cnt;
}

static long step(const std::string& n) {
	for (int i = 0; i <= 1; ++i)
		for (int j = 0; j <= BOOP; ++j)
			dp[i][j] = -1;
	return go(0,true,n,0,0);
}

static void one_case(const std::string& l, const std::string& r) {
	std::printf("%ld\n", step(r) - step(l));
}

int main(void) {



	int t;
	std::scanf("%d", &t);

	long l,r;
	while(t-->0) {
		std::scanf("%ld %ld", &l, &r);

		if (!l && !r) {
			std::printf("0\n");
			continue;
		}

		one_case(std::bitset<BOOP>(std::max(0L, l-1)).to_string(), std::bitset<BOOP>(r).to_string());
	}

	return 0;
}
