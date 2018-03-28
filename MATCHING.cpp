#include <bits/stdc++.h>

#define FI first
#define SE second

typedef long long ll;

struct HopcroftKarp {
	typedef long long ll;

	struct Node {
		ll id;
		ll level;

		Node* pair;
		std::vector<Node*> adj;

		bool used;

		Node(const ll& ii)
			: id(ii), level(-1), pair(nullptr), used(false) {}
	};

	ll n;
	std::vector<Node*> graph;

	HopcroftKarp(const ll& nn) {
		n = nn;
		graph.resize(n);
		for (ll i = 0; i < n; ++i)
			graph[i] = new Node(i);
	}

	~HopcroftKarp(void) {
		for (Node* e : graph)
			delete e;
	}

	void add_edge(const ll& a, const ll& b) {
		if (!graph[a] || !graph[b]) return;
		graph[a]->adj.push_back(graph[b]);
		graph[b]->adj.push_back(graph[a]);
	}

	/* matches the graph. */
	ll match(void) {
		for (ll match = 0; ;) {
			std::queue<Node*> order;
			for (auto& node : graph) {
				node->level = -1;
				if (node->pair == nullptr) {
					node->level = 0;
					order.push(node);
				}
			}

			while (!order.empty()) {
				Node* curr = order.front(); order.pop();
				for (auto& neigh : curr->adj) {
					Node* w = neigh->pair;
					if (w != nullptr && w->level < 0) {
						w->level = curr->level + 1;
						order.push(w);
					}
				}
			}

			for (auto& node : graph)
				node->used = false;

			ll d = 0;
			for (auto& node : graph)
				d += node->pair == nullptr && dfs(node);

			match += d;

			/* the end */
			if (d == 0) return match;
		}
	}

	bool dfs(Node* curr) {
		curr->used = true;
		for (auto& neigh : curr->adj) {
			Node* w = graph[neigh->id]->pair;
			if (w == nullptr || !w->used && curr->level < w->level && dfs(w)) {
				curr->pair = neigh;
				neigh->pair = curr;
				return true;
			}
		}
		return false;
	}
};

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	ll n, m, p;
	std::cin >> n >> m >> p;

	HopcroftKarp HK(n + m);
	for (ll a,b; p--;) {
		std::cin >> a >> b;
		HK.add_edge(a-1, b-1 + n);
	}

	std::cout << HK.match() << "\n";

	return 0;
}
