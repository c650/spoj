#include <bits/stdc++.h>

#define FI first
#define SE second

typedef long long ll;
typedef std::pair<ll,ll> pairll;

const static ll INF = 0x3f3f3f3f3f3f3f3f;

namespace FFT {
	typedef long long ll;

	using cd = std::complex<double>;
	const double PI = std::acos(-1);

	void fft(std::vector<cd>& a, const bool& invert) {
		ll n = a.size();

		for (ll i = 1, j = 0; i < n; ++i) {
			ll bit = n >> 1;
			for (; j & bit; bit >>= 1)
				j ^= bit;
			j ^= bit;

			if (i < j)
				std::swap(a[i], a[j]);
		}

		for (ll len = 2; len <= n; len <<= 1) {
			const double ang = 2 * PI / len * (invert ? -1 : 1);
			cd wlen(std::cos(ang), std::sin(ang));
			for (ll i = 0; i < n; i += len) {
				cd w(1);
				for (ll j = 0; j < len / 2; ++j) {
					cd u = a[i+j], v = a[i+j+len/2] * w;
					a[i+j] = u+v;
					a[i+j+len/2] = u-v;
					w *= wlen;
				}
			}
		}

		if (invert) {
			for (auto& x : a)
				x /= n;
		}
	}

	std::vector<ll> multiply(const std::vector<ll>& a, const std::vector<ll>& b) {
		std::vector<cd> fa(a.begin(),a.end()), fb(b.begin(), b.end());
		ll n = 1;
		while (n < a.size() + b.size())
			n <<= 1;
		fa.resize(n);
		fb.resize(n);

		fft(fa, false);
		fft(fb, false);

		for (ll i = 0; i < n; ++i)
			fa[i] *= fb[i];

		fft(fa, true);

		std::vector<ll> result(n);
		for (ll i = 0; i < n; ++i)
			result[i] = std::llround(fa[i].real());

		return result;
	}

	/* if it's numbers and not polynomials, we have to normalise */
	void normalise(std::vector<ll>& result) {
		for (ll i = 0, carry = 0; i < result.size(); ++i) {
			result[i] += carry;
			carry = result[i] / 10;
			result[i] %= 10;
		}
	}
};

static inline void setio(void);

static void one_case(void) {
	ll n; std::cin >> n;
	std::vector<ll> a(n+1), b(n+1);
	for (auto& e : a) std::cin >> e;
	for (auto& e : b) std::cin >> e;

	std::vector<ll> res = FFT::multiply(a, b);
	for (ll i = 0; i <= 2 * n; ++i)
		std::cout << res[i] << " ";
	std::cout << '\n';
}

int main(void) {
	setio();
	ll n; std::cin >> n;
	while (n--) one_case();
	return 0;
}

static inline void setio(void) {
	std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
	std::cout.precision(10); std::cout << std::fixed;
}
