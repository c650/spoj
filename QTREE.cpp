#include <bits/stdc++.h>

typedef int ll;

struct BinaryLiftingGraph {
	typedef long long ll;
	const ll INF = 98765432100LL;

	const ll root = 0;
	ll n;
	std::vector<std::vector<ll>> graph;
	std::vector<std::vector<ll>> table;
	std::vector<ll> depth;
	bool unbuilt;

	BinaryLiftingGraph(const ll& _n) : n(_n) {
		graph.resize(n);
		unbuilt = true;
	}

	void add_edge(const ll& a, const ll& b) {
		graph[a].push_back(b);
		graph[b].push_back(a);
		unbuilt = true;
	}

	/* run this before queries. */
	void build(void) {
		if (!unbuilt) return;
		unbuilt = false;

		table.assign(std::ceil(std::log2(n))+1, std::vector<ll>(n,-1));
		depth.assign(n, INF);

		std::queue<ll> order;
		order.push(root);
		depth[root] = 0;

		while (!order.empty()) {
			ll cur = order.front();
			order.pop();

			for (const auto& neigh : graph[cur]) {
				if (depth[neigh] > 1 + depth[cur]) {
					depth[neigh] = 1 + depth[cur];
					table[0][neigh] = cur;
					order.push(neigh);
				}
			}
		}

		for (ll deep = 1; deep < static_cast<ll>(table.size()); ++deep) {
			for (ll node = 0; node < n; ++node){
				ll mid = table[deep-1][node];
				if (mid != -1)
					table[deep][node] = table[deep-1][mid];
			}
		}
	}

	ll walk(ll node, const ll& k) {
		build();
		for (ll i = 0; i < static_cast<ll>(table.size()) && node != -1; ++i) {
			if (k & (1 << i))
				node = table[i][node];
		}
		return node;
	}

	ll get_lca(ll a, ll b) {
		build();
		if (depth[a] > depth[b])
			a = walk(a, depth[a] - depth[b]);
		else if (depth[b] > depth[a])
			b = walk(b, depth[b] - depth[a]);

		if (a == b) {
			return a;
		}

		for (ll i = table.size()-1; i >= 0; --i) {
			if (table[i][a] != table[i][b]) {
				a = table[i][a];
				b = table[i][b];
			}
		}

		return walk(a,1);
	}

	/* returns edge distance between two nodes in tree. */
	ll dist(const ll& a, const ll& b) {
		build();
		return depth[a] + depth[b] - 2 * depth[get_lca(a,b)];
	}
};

template <ll MAX_N>
struct st {
	const ll n;
	ll max[4 * MAX_N + 1];

	st(const ll& _n) : n(_n) {
		memset(max, 0, sizeof(max));
	}

	void upd(const ll& l, const ll& v) {
		upd(0, 0, n-1, l, v);
	}

	void upd(const ll& i, const ll& rl, const ll& rr, const ll& l, const ll& v) {
		if (rl == l && rr == l) {
			max[i] = v;
		} else {
			ll mid = (rl + rr) / 2;
			if (l <= mid)
				upd(2 * i + 1, rl, mid, l, v);
			else
				upd(2 * i + 2, mid+1, rr, l, v);
			max[i] = std::max(max[2*i+1], max[2*i+2]);
		}
	}

	ll qry(const ll& l, const ll& r) const {
		return qry(0, 0, n-1, l, r);
	}

	ll qry(const ll& i, const ll& rl, const ll& rr, const ll& l, const ll& r) const {
		if (rl == l && rr == r) {
			return max[i];
		}
		ll mid = (rl + rr) / 2;
		ll ret = 0;
		if (l <= mid)
			ret = std::max(ret, qry(2*i+1, rl, mid, l, std::min(mid,r)));
		if (mid < r)
			ret = std::max(ret, qry(2*i+2, mid+1, rr, std::max(mid+1,l), r));
		return ret;
	}
};

template <ll MAX_N>
struct hld {

	struct edge {
		ll a, b, id;
		bool heavy;
	};

	const ll n; ll edge_count;
	std::vector<edge> gr[MAX_N];
	ll edge_weights[MAX_N], edge_order[MAX_N], edge_map[MAX_N];

	// dfs stuff
	ll po, pre[MAX_N], skip[MAX_N], sub[MAX_N], dep[MAX_N];
	edge parent[MAX_N];

	// decomp stuff
	ll chain_head[MAX_N], first_edge[MAX_N], last_edge[MAX_N], in_chain[MAX_N], pos_in_chain[MAX_N], max_kid[MAX_N], chain_count;

	st<MAX_N> segtree;

	hld(const ll& _n) : n(_n), edge_count(0), segtree(_n) {
		memset(chain_head, 0xff, sizeof(chain_head));
		memset(first_edge, 0xff, sizeof(first_edge));
		memset(last_edge , 0xff, sizeof(last_edge));
	}

	void add_edge(const ll& a, const ll& b, const ll& c = 1) {
		gr[a].push_back(edge{a,b,edge_count,false});
		gr[b].push_back(edge{b,a,edge_count,false});
		edge_weights[edge_count++] = c;
	}

	void run(void) {
		po = 0; dfs(0, -1);

		edge_count = 0;
		decomp(0, -1, chain_count = 0);
		for (ll i = 0; i < edge_count; ++i) {
			segtree.upd(edge_order[i], edge_weights[i]);
		}
	}

	ll dfs(const ll& cur, const ll& par) {
		pre[cur] = po++;
		sub[cur] = 1;
		dep[cur] = par >= 0 ? dep[par] + 1 : 0;
		for (const auto& nei : gr[cur]) {
			if (nei.b != par) {
				parent[nei.b] = nei;
				sub[cur] += dfs(nei.b, cur);
			}
		}
		skip[cur] = po-1;
		return sub[cur];
	}

	void decomp(const ll& cur, const ll& par, const ll& cc) {
		if (chain_head[cc] < 0) chain_head[cc] = cur;
		else edge_map[parent[cur].id] = cc;

		in_chain[cur] = cc;
		pos_in_chain[cur] = dep[cur] - dep[chain_head[cc]];

		ll max_sub = 0; max_kid[cur] = -1;
		for (const auto& nei : gr[cur]) {
			if (nei.b != par && max_sub < sub[nei.b]) {
				max_sub = sub[max_kid[cur] = nei.b];
			}
		}

		if (max_kid[cur] == -1) {
			last_edge[cc] = chain_head[cc] == cur ? -1 : parent[cur].id;
			return ;
		}

		if (chain_head[cc] == cur) {
			first_edge[cc] = parent[max_kid[cur]].id;
		}
		edge_order[parent[max_kid[cur]].id] = edge_count++;
		decomp(max_kid[cur], cur, cc);

		for (const auto& nei : gr[cur]) {
			if (nei.b == par || nei.b == max_kid[cur]) continue;
			edge_order[nei.id] = edge_count++;
			decomp(nei.b, cur, ++chain_count);
		}
	}

	ll qry(const ll& node, const ll& ancestor) {
		ll ret = 0;
		ll cur = node;
		for (; in_chain[cur] != in_chain[ancestor]; ) {
			if (first_edge[in_chain[cur]] >= 0) {
				ret = std::max(ret, segtree.qry(edge_order[first_edge[in_chain[cur]]], edge_order[parent[cur].id]));
			}
			cur = chain_head[in_chain[cur]];
			ret = std::max(ret, edge_weights[parent[cur].id]);
			cur = parent[cur].a;
		}

		if (cur != ancestor) {
			ret = std::max(ret, segtree.qry(edge_order[parent[max_kid[ancestor]].id], edge_order[parent[cur].id]));
		}
		return ret;
	}

	void upd(const ll& edge_id, const ll& val) {
		segtree.upd(edge_order[edge_id], edge_weights[edge_id] = val);
	}
};

static inline void setio(void);

int main(void) {
	setio();

	ll t; std::cin >> t;

	while (t--) {
		ll n; std::cin >> n;

		hld<10001> tree(n);
		BinaryLiftingGraph lifty(n);

		for (ll i = 1, a,b,c; i < n; ++i) {
			std::cin >> a >> b >> c;
			tree.add_edge(a-1, b-1, c);
			lifty.add_edge(a-1, b-1);
		}

		tree.run();
		lifty.build();

		// for (ll i = 0; i < n; ++i) {
		// 	std::cerr << "node " << i+1 << " is in the chain " << tree.in_chain[i] << "\n";
		// }

		for (;;) {
			std::string type; std::cin >> type;
			if (type == "DONE") break;
			else if (type == "CHANGE") {
				ll id, cost; std::cin >> id >> cost;
				tree.upd(id-1, cost);
			} else {
				ll a, b, lca; std::cin >> a >> b;
				lca = lifty.get_lca(a-1,b-1);
				// std::cerr << "lca of " << a << " and " << b << " is " << lca+1 << "\n";
				std::cout << std::max(tree.qry(a-1, lca), tree.qry(b-1, lca)) << "\n";
			}
			// std::cout << std::flush;
		}
	}

	// std::cerr << static_cast<double>(clock())/CLOCKS_PER_SEC << "\n";

	return 0;
}

static inline void setio(void) {
	std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
	std::cout.precision(10); std::cout << std::fixed;
}
