#include <bits/stdc++.h>

/* [eq][num3][num6][num9][k] */
long long dp[2][51][51][51][51];

long long ans[101];

/* three count, six count, nine count, */
static long long go(const int& tc, const int& sc, const int& nc, const std::string& bound, bool eq, const int& k) {
	if (k >= bound.size()) {
		return tc >= 1 && tc == sc && tc == nc;
	}

	if (dp[eq][tc][sc][nc][k] != -1) {
		return dp[eq][tc][sc][nc][k];
	}

	int top = eq ? bound.at(k) - '0' : 9;

	long long cnt = 0;
	for (int i = 0; i <= top; ++i) {
		cnt += go(tc + (i == 3), sc + (i == 6), nc + (i == 9), bound, eq && i == top, k+1);
		if (cnt >= 1000000007)
			cnt %= 1000000007;
	}

	// std::printf("go(%d,%d,%d,,%d,%d) -> %lld\n", tc,sc,nc,eq,k, cnt);

	return dp[eq][tc][sc][nc][k] = cnt % 1000000007;
}

static long long sub(const std::string& num) {
	for (int i = 0; i < 51; ++i) {
		for (int j = 0; j < 51; ++j) {
			for (int k = 0; k < 51; ++k) {
				for (int l = 0; l < 51; ++l) {
					dp[0][i][j][k][l] = dp[1][i][j][k][l] = -1;
				}
			}
		}
	}

	return go(0,0,0,num, true, 0);
}

static bool is_369(const std::string& s) {
	int tc,sc,nc;
	tc = sc = nc = 0;
	for (const auto& c : s) {
		tc += c == '3';
		sc += c == '6';
		nc += c == '9';
	}
	return tc >= 1 && tc == sc && tc == nc;
}

static long long one_case(const std::string& l, const std::string& r) {
	long long a = sub(r);
	long long b = sub(l);

	return (a - b < 0 ? 1000000007L + a - b : a - b) + is_369(l);
}

int main(void) {
	int t;
	std::scanf("%d", &t);

	std::string l,r;
	for (int i = 0; i < t; ++i) {
		std::cin >> l >> r;
		ans[i] = one_case(l,r);
	}

	for (int i = 0; i < t; ++i) {
		std::printf("%lld\n", ans[i]);
	}

	return 0;
}
