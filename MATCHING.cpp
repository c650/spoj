#include <bits/stdc++.h>

#define FI first
#define SE second

typedef long long ll;

const static ll INF = std::numeric_limits<int>::max();
struct DinicFlow {

	struct edge {
		ll a, b;
		ll flow,cap;

		edge* rev;

		edge(const ll& _a, const ll& _b, const ll& _flow, const ll& _cap, edge* _rev = nullptr)
			: a(_a), b(_b), flow(_flow), cap(_cap), rev(_rev) {}
	};

	typedef std::vector<std::vector< edge* >> adj_list;

	/* for the DFS part */
	std::vector<char> blocked;

	/* for the BFS part */
	std::vector<ll> distances;

	adj_list graph;

	ll n; /* number of nodes */
	ll source;
	ll sink;

	/* intakes the number of nodes in the graph */
	DinicFlow(const ll& _n) : n(_n) {
		source = n++; /* idk why */
		sink = n++;

		blocked.assign(n, false);
		distances.assign(n, INF);

		graph.assign(n, std::vector<edge*>());
	}

	~DinicFlow(void) {
		/* gotta free that memory!*/
		for (auto& row : graph) {
			for (auto& e : row) {
				delete e;
			}
		}
	}

	/* add the directed edge, and it adds the backedge for you */
	void add_edge(const ll& a, const ll& b, const ll& cap, const ll& flow = 0) {
		edge* normal = new edge(a,b,flow,cap);
		edge* reverse = normal->rev = new edge(b,a,0,0, normal);

		graph[a].push_back(normal);
		graph[b].push_back(reverse);

		if (!normal || !reverse) {
			std::fprintf(stderr,"fail\n");
		}
	}

	bool bfs(void) {
		distances.assign(n, INF);
		distances[sink] = 0;

		std::queue<ll> order;
		order.push(sink);

		while (!order.empty()) {
			ll best = order.front();
			order.pop();

			if (best == source) return true;

			for (edge* neigh : graph[best]) {
				if (neigh->rev->cap > neigh->rev->flow && distances[neigh->b] > 1 + distances[best]) {
					distances[neigh->b] = 1 + distances[best];
					order.push(neigh->b);
				}
			}
		}

		return false;
	}

	ll dfs(const ll& pos, const ll& min) {
		if (pos == sink) {
			return min;
		}

		ll flow = 0;
		for (edge* e : graph[pos]) {
			ll curr = 0;
			if (!blocked[e->b] && distances[e->b] == distances[pos] - 1 && e->cap > e->flow) {
				curr = dfs(e->b, std::min(min - flow, e->cap - e->flow));
				e->flow += curr;
				e->rev->flow = -(e->flow);
				flow += curr;
			}
			if (flow == min) return flow;
		}
		blocked[pos] = flow != min;
		return flow;
	}

	ll flow(void) {
		for (auto& row : graph) {
			for (edge* e : row)
				e->flow = 0;
		}

		ll ret = 0;
		while(bfs()) {
			blocked.assign(blocked.size(), false);
			ret += dfs(source, INF);
		}
		return ret;
	}
};

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	ll n, m, p;
	std::cin >> n >> m >> p;

	DinicFlow df(n + m);
	for (ll a,b; p--;) {
		std::cin >>a >> b;
		df.add_edge(a-1, b-1 + n, 1);
	}

	for (ll i = 0; i < n; ++i)
		df.add_edge(df.source, i, 1);
	for (ll i = 0; i < m; ++i)
		df.add_edge(i + n, df.sink, 1);

	std::cout << df.flow() << "\n";

	return 0;
}
