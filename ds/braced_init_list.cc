/**
 *  braced-init-list
 *  ================
 *
 *  Some hacks on braced-init-list.
 *
 *  Note: Compile with -std=c++17
 */

#include <iostream>

int
main()
{
	for (auto x : {4, 2, 6, 9}) {
		std::cout << x << std::endl;
	}
	return 0;
}
