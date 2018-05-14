#include <bits/stdc++.h>

typedef long long ll;

static inline void setio(void);

template <class Sequence>
struct KMP {
	typedef long long ll;

	const ll n;

	/* kmp table. */
	std::vector<ll> p;
	const Sequence needle;

	KMP(const Sequence& _needle) : needle(_needle), n(_needle.size()) {
		/* compute the table */
		p.assign(n+1, 0);
		p[0] = -1; p[1] = 0;
		for (ll i = 2, k = 0; i <= n; ++i) {
			while (k > 0 && needle[k] != needle[i-1])
				k = p[k];
			p[i] = needle[k] == needle[i-1] ? ++k : 0;
		}
	}

	std::vector<ll> find_occurences_in(const Sequence& haystack) const {
		std::vector<ll> locs;
		actual_kmp_search(haystack, true, locs);
		return locs;
	}

	ll count_occurences_in(const Sequence& haystack) const {
		return actual_kmp_search(haystack);
	}

private:

	/* search for the needle in the haystack. */
	ll actual_kmp_search(const Sequence& haystack, const bool& fill_vec = false, std::vector<ll>& locs = std::vector<ll>()) const {
		ll cnt = 0;
		for (ll i = 0, k = 0; i < haystack.size(); ++i) {
			while (k > 0 && needle[k] != haystack[i])
				k = p[k];
			if (needle[k] == haystack[i])
				++k;
			if (k == needle.size()) {
				if (fill_vec) locs.push_back(i);
				++cnt;
				k = p[k];
			}
		}
		return cnt;
	}
};

static void one_case(void) {
	std::string A,B;
	std::cin >> A >> B;

	KMP<std::string> pat(B);

	std::vector<ll> ret = pat.find_occurences_in(A);
	if (ret.empty()) {
		std::cout << "Not Found\n";
	} else {
		std::cout << ret.size() << "\n";
		for (const auto& pos : ret)
			std::cout << pos - B.length() + 2 << " ";
		std::cout << "\n";
	}
}

int main(void) {
	setio();

	ll n; std::cin >> n;
	while (n--) {
		one_case();
		std::cout << "\n";
	}

	return 0;
}

static inline void setio(void) {
	std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
	std::cout.precision(10); std::cout << std::fixed;
}
