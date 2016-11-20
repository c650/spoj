#include <iostream>
#include <set>

static int smaller_or_eq(const std::multiset<int>& s , const int y) {
	return std::distance(s.begin(), s.upper_bound(y));
}
 
// static void pset(const std::multiset<int>& myset) {
// 	for (auto& e : myset) {
// 		std::cout << e << " ";
// 	}
// 	std::cout << std::endl;
// }

int main() {

	int n,q;
	std::cin >> n >> q;

	std::multiset<int> myset;
	int tmp;
	while(n-->0) {
		std::cin >> tmp;
		myset.insert(tmp);
	}

	int _q;
	while(q-->0) {
		std::cin >> _q >> tmp;

		// pset(myset);

		switch (_q) {
			case 1:
				myset.insert( smaller_or_eq(myset, tmp) + tmp );
				// std::cout << _q << " " << tmp << " ->";
				// pset(myset);
				break;
			case 2:
				std::cout /*<< _q << " " << tmp << " ->"*/ << smaller_or_eq(myset, tmp) << std::endl;
				break;
			case 3:
				if (size_t(tmp) >= myset.size()) {
					std::cout << "invalid\n";
				} else {
					auto itr = myset.begin();
					std::advance(itr, tmp-1);
					std::cout /*<< _q << " " << tmp << " ->" */<< *(itr) << std::endl;
				}
		}
	}




	return 0;

}
