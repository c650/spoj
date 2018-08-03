#include <bits/stdc++.h>

#define FI first
#define SE second

typedef long long ll;
typedef std::pair<ll,ll> pairll;

const static ll INF = 0x3f3f3f3f3f3f3f3f;

static inline void setio(void);

template<ll LOG, ll MAX_N>
struct binary_lifting_graph {

	const ll n, root;
	ll lift[LOG][MAX_N];
	ll depth[MAX_N], dist[MAX_N];

	std::vector<pairll> gr[MAX_N];

	binary_lifting_graph(const ll& _n) : n(_n), root(0) {
		memset(lift, 0xff, sizeof(lift));
		memset(depth, 0x3f, sizeof(depth));
		memset(dist, 0x3f, sizeof(dist));
	}

	void add_edge(const ll& a, const ll& b, const ll& c) {
		gr[a].push_back({b, c});
		gr[b].push_back({a, c});
	}

	void run(void) {
		depth[root] = dist[root] = 0;
		std::queue<ll> order;
		order.push(root);
		while (!order.empty()) {
			ll cur = order.front(); order.pop();
			for (const auto& nei : gr[cur]) {
				if (depth[nei.FI] > 1 + depth[cur]) {
					dist[nei.FI] = nei.SE + dist[cur];
					depth[nei.FI] = 1 + depth[cur];
					lift[0][nei.FI] = cur;
					order.push(nei.FI);
				}
			}
		}

		for (ll lg = 1; lg < LOG; ++lg) {
			for (ll i = 0; i < n; ++i) {
				ll mid = lift[lg-1][i];
				if (mid != -1)
					lift[lg][i] = lift[lg-1][mid];
			}
		}
	}

	ll walk(ll i, const ll& k) const {
		for (ll lg = LOG-1; lg >= 0; --lg) {
			if (k & (1 << lg))
				i = lift[lg][i];
		}
		return i;
	}

	ll get_lca(ll a, ll b) const {
		if (depth[a] > depth[b])
			a = walk(a, depth[a] - depth[b]);
		if (depth[b] > depth[a])
			b = walk(b, depth[b] - depth[a]);

		if (a == b) return a;

		for (ll lg = LOG-1; lg >= 0; --lg) {
			if (lift[lg][a] != lift[lg][b]) {
				a = lift[lg][a];
				b = lift[lg][b];
			}
		}

		return walk(a, 1);
	}

	ll get_weighted_dist(const ll& a, const ll& b) const {
		return dist[a] + dist[b] - 2 * dist[get_lca(a,b)];
	}

	ll get_uweighted_dist(const ll& a, const ll& b) const {
		return depth[a] + depth[b] - 2 * depth[get_lca(a,b)];
	}
};

int main(void) {
	setio();

	ll t; std::cin >> t;
	while (t--) {
		ll n; std::cin >> n;

		binary_lifting_graph<15, 10001> gr(n);
		for (ll i = 1, a,b,c; i < n; ++i) {
			std::cin >> a >> b >> c;
			gr.add_edge(a-1,b-1,c);
		}

		gr.run();

		for (std::string type; ; ) {
			std::cin >> type;
			if (type == "DONE") break;
			else if (type == "DIST") {
				ll a, b; std::cin >> a >> b;
				std::cout << gr.get_weighted_dist(a-1, b-1) << "\n";
			} else {
				ll a,b,k; std::cin >> a >> b >> k;
				const ll lca = gr.get_lca(--a, --b);

				const ll atolca = gr.get_uweighted_dist(a, lca) + 1;
				if (atolca >= k) {
					std::cout << gr.walk(a, k-1)+1 << "\n";
				} else {
					k -= atolca;
					std::cout << gr.walk(b, gr.get_uweighted_dist(b, lca) - k)+1 << "\n";
				}
			}
		}
	}

	return 0;
}

static inline void setio(void) {
	std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
	std::cout.precision(10); std::cout << std::fixed;
}
