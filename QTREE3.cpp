#include <bits/stdc++.h>

typedef int ll;

const static ll INF = 0x3f3f3f3f;

static inline void setio(void);

template <ll MAX_N>
struct st {
	const ll n;
	ll min[4 * MAX_N + 1];

	st(const ll& _n) : n(_n) {
		memset(min, 0x3f, sizeof(min));
	}

	void upd(const ll& l, const ll& v) {
		upd(0, 0, n-1, l, v);
	}

	void upd(const ll& i, const ll& rl, const ll& rr, const ll& l, const ll& v) {
		if (rl == l && rr == l) {
			min[i] = v;
		} else {
			ll mid = (rl + rr) / 2;
			if (l <= mid)
				upd(2 * i + 1, rl, mid, l, v);
			else
				upd(2 * i + 2, mid+1, rr, l, v);
			min[i] = std::min(min[2*i+1], min[2*i+2]);
		}
	}

	ll qry(const ll& l, const ll& r) const {
		return qry(0, 0, n-1, l, r);
	}

	ll qry(const ll& i, const ll& rl, const ll& rr, const ll& l, const ll& r) const {
		if (rl == l && rr == r) {
			return min[i];
		}
		ll mid = (rl + rr) / 2;
		ll ret = INF;
		if (l <= mid)
			ret = std::min(ret, qry(2*i+1, rl, mid, l, std::min(mid,r)));
		if (mid < r)
			ret = std::min(ret, qry(2*i+2, mid+1, rr, std::min(mid+1,l), r));
		return ret;
	}
};

template <ll MAX_N>
struct hld {
	struct edge {
		ll a, b;
	};

	const ll n;
	std::vector<edge> gr[MAX_N];

	ll sub[MAX_N], dep[MAX_N];
	edge parent[MAX_N];

	ll chain_head[MAX_N], in_chain[MAX_N],
	   t_order[MAX_N], inv_t_order[MAX_N],
	   max_kid[MAX_N], po, chain_count;

	st<MAX_N> segtree;

	char is_black[MAX_N];

	hld(const ll& _n) : n(_n), segtree(_n) {
		memset(chain_head, 0xff, sizeof(chain_head));
		memset(is_black, 0, sizeof(is_black));
	}

	void add_edge(const ll& a, const ll& b) {
		gr[a].push_back({a, b});
		gr[b].push_back({b, a});
	}

	void run(void) {
		dfs(0, -1);

		po = 0;
		decomp(0, -1, chain_count = 0);
	}

	ll dfs(const ll& cur, const ll& par) {
		dep[cur] = par >= 0 ? dep[par] + 1 : 0;
		sub[cur] = 1;
		for (const auto& nei : gr[cur]) {
			if (nei.b != par) {
				parent[nei.b] = nei;
				sub[cur] += dfs(nei.b, cur);
			}
		}
		return sub[cur];
	}

	void decomp(const ll& cur, const ll& par, const ll& cc) {
		if (chain_head[cc] < 0) chain_head[cc] = cur;

		in_chain[cur] = cc;
		t_order[cur] = po++;
		inv_t_order[t_order[cur]] = cur;

		ll max_sub = 0; max_kid[cur] = -1;
		for (const auto& nei : gr[cur]) {
			if (nei.b != par && max_sub < sub[nei.b]) {
				max_sub = sub[max_kid[cur] = nei.b];
			}
		}

		if (max_kid[cur] == -1) return; // importante

		decomp(max_kid[cur], cur, cc);

		for (const auto& nei : gr[cur]) {
			if (nei.b == par || nei.b == max_kid[cur]) continue;
			decomp(nei.b, cur, ++chain_count);
		}
	}

	ll qry(const ll& node, const ll& ancestor) {
		ll ret = INF, cur = node;
		for (; in_chain[cur] != in_chain[ancestor]; ) {
			ret = std::min(ret, segtree.qry(t_order[chain_head[in_chain[cur]]], t_order[cur]));
			cur = parent[chain_head[in_chain[cur]]].a;
		}
		ret = std::min(ret, segtree.qry(t_order[ancestor], t_order[cur]));
		if (ret == INF) return -1;
		else return inv_t_order[ret]+1;
	}

	void upd(const ll& node) {
		if (is_black[node]) {
			segtree.upd(t_order[node], INF);
		} else {
			segtree.upd(t_order[node], t_order[node]);
		}
		is_black[node] = !is_black[node];
	}
};

int main(void) {
	setio();

	ll n, q; std::cin >> n >> q;

	hld<100001> gr(n);
	for (ll i = 1, a, b; i < n; ++i) {
		std::cin >> a >> b;
		gr.add_edge(a-1, b-1);
	}

	gr.run();

	while (q--) {
		ll type, v; std::cin >> type >> v;
		if (type == 0)
			gr.upd(v-1);
		else std::cout << gr.qry(v-1, 0) << "\n";
	}

	return 0;
}

static inline void setio(void) {
	std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
	std::cout.precision(10); std::cout << std::fixed;
}
