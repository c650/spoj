#include <bits/stdc++.h>

#define FI first
#define SE second

typedef long long ll;
typedef std::pair<ll,ll> pairll;

const static ll INF = 98765432100LL;

static inline void setio(void);

const ll MAX_SIEVE_NUM = 10000002;
const ll NUM_PRIMES = 664579;
ll *primes;

std::unordered_map<ll,ll> rank;

static void one_case(void) {
	for (ll i = 0; i < NUM_PRIMES; ++i)
		primes[i] = std::abs(primes[i]);

	ll n; std::cin >> n;
	for (ll num; n--; ) {
		std::cin >> num;
			for (ll i = 2, lim = std::ceil(std::sqrt(num)); i <= lim && num > 1; ++i) {
			if (num % i) continue;
			primes[rank[i]] = -std::abs(primes[rank[i]]);
			while (num % i == 0) num /= i;
		}
		if (num > 1) primes[rank[num]] = -std::abs(primes[rank[num]]);
	}
	ll ans = 0;
	for (; ans < NUM_PRIMES && primes[ans] <= 0; ++ans);
	std::cout << primes[ans] << "\n";
}

int main(void) {
	setio();

	primes = new ll[NUM_PRIMES];

	char *sieve = new char[MAX_SIEVE_NUM];
	std::fill(sieve, sieve+MAX_SIEVE_NUM, true);
	sieve[0] = sieve[1] = false;

	for (ll i = 2, cnt = 0; i < MAX_SIEVE_NUM; ++i) {
		if (!sieve[i]) continue;

		rank[i] = cnt;
		primes[cnt++] = i;

		for (ll j = i+i; j < MAX_SIEVE_NUM; j += i)
			sieve[j] = false;
	}

	delete [] sieve;

	ll n; std::cin >> n;
	while (n--) one_case();

	delete [] primes;

	return 0;
}

static inline void setio(void) {
	std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
	std::cout.precision(10); std::cout << std::fixed;
}
