/**
 *  if init
 *  =======
 *
 *  if-statement with initialization.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>

int
main()
{
	int n;

	if (std::cin >> n; n != 42) {
		std::cout << "wut" << std::endl;
	} else {
		std::cout << "the truth" << std::endl;
	}

	return 0;
}
