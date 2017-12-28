/**
 *  Rounding
 *  ========
 *
 *  Some rounding strategies.
 */

#include <iostream>

template <typename T>
T
round_half_up(double i)
{
	return static_cast<T>(i + 0.5);
}

int
main()
{
	std::cout << round_half_up<int>(4.2) << std::endl;
	std::cout << round_half_up<int>(6.9) << std::endl;
	return 0;
}
