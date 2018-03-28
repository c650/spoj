#include <bits/stdc++.h>

#define FI first
#define SE second

typedef long long ll;

struct Trie {
	const static ll ALPHA = 26;
	const static char ALPHA_BEG = 'a';

	struct TrieNode {
		ll count;
		char value;

		ll all_count;

		std::vector<TrieNode*> next;
		TrieNode* parent;

		TrieNode* max;
		ll max_len;

		TrieNode(const char& val, TrieNode* p = nullptr) {
			value = val;
			count = 0;
			next.assign(ALPHA, nullptr);
			parent = p;

			max = nullptr;
			max_len = 0;

			all_count = 0;
		}

		~TrieNode(void) {
			for (auto& e : next)
				if (e != nullptr)
					delete e;
		}

		/* returns how many words have `this` as prefix*/
		ll count_all(void) {
			return all_count;
		}

		// TrieNode* do_max(void) {

		// }
	};

	/* the ROOT */
	TrieNode* root;

	Trie(void) {
		root = new TrieNode('$', nullptr);
	}

	~Trie(void) {
		delete root;
	}

	/* inserts a string. makes nodes as needed. */
	void insert(const std::string& s) {
		TrieNode* curr = this->root;

		for (ll i = 0; i < s.length(); ++i) {
			ll tmp = std::tolower(s[i]) - ALPHA_BEG;
			if (curr->next[tmp] == nullptr)
				curr->next[tmp] = new TrieNode(tmp + ALPHA_BEG, curr);
			curr = curr->next[tmp];
		}

		auto end = curr;
		ll len = 0;
		curr->count++;

		for(; curr != nullptr; curr = curr->parent, ++len) {
			if (curr->max == nullptr || curr->max->count <= end->count) {
				curr->max = end;
				curr->max_len = len;
			}
			curr->all_count++;
		}
	}

	/* removes a string if it was there. */
	void remove(const std::string& s) {
		TrieNode* curr = find_end(s);
		if (curr == nullptr) return;

		curr->count--;

		for (; curr != nullptr; curr = curr->parent)
			curr->all_count--;
	}

	/*	finds the last node of entry of `s` if it's there
		returns nullptr otherwise. */
	TrieNode* find_end(const std::string& s) const {
		TrieNode* curr = this->root;

		for (ll i = 0; i < s.length(); ++i) {
			ll tmp = std::tolower(s[i]) - ALPHA_BEG;
			if (curr->next[tmp] == nullptr)
				return nullptr;
			curr = curr->next[tmp];
		}

		return curr;
	}

	std::string build(const TrieNode* end) const {
		std::stringstream ss;
		for (auto i = end; i != nullptr && i->parent != nullptr; i = i->parent)
			ss << i->value;
		std::string s = ss.str();
		std::reverse(s.begin(),s.end());
		return s;
	}

	/* returns how many instances of `s` are in trie. */
	ll count(const std::string& s) const {
		TrieNode* ret = find_end(s);
		return ret == nullptr ? 0 : ret->count;
	}

	/*	returns how many strings
		are in the entire trie
		with root as prefix. */
	ll count_all(void) const {
		return this->root->count_all();
	}

	/* returns true if the string is in the trie. */
	bool find(const std::string& s) const {
		return count(s) > 0;
	}
};


int main(void) {
	std::ios::sync_with_stdio(false); std::cin.tie(nullptr);

	Trie tr;

	ll n; std::cin >> n;
	std::vector<std::string> vec(n);
	for (auto& e : vec)
		std::cin >> e;

	std::sort(vec.rbegin(),vec.rend());
	for (auto& e : vec)
		tr.insert(e);

	std::string s;
	ll q; std::cin >> q;
	while (q--) {
		std::cin >> s;
		auto node = tr.find_end(s);
		if (node == nullptr) {
			std::cout << "-1";
		} else {
			std::cout << tr.build(node->max) << " " << node->max->count;
		}
		std::cout << "\n";
	}

	return 0;
}
