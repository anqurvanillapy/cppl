/**
 *  Multimap
 *  ========
 *
 *  Map but permits multiple entries with the same key.
 */

#include <iostream>
#include <map>

int
main()
{
	std::multimap<int, std::string> m = {
		{42, "foo"},
		{42, "bar"},
		{69, "baz"},
	};

	auto range = m.equal_range(42);
	for (auto i = range.first; i != range.second; ++i) {
		std::cout << i->first << ", " << i->second << std::endl;
	}
	return 0;
}
