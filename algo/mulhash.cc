/**
 *  Multiplicative hashing
 *  ======================
 *
 *  Based on the golden ratio, so A.K.A. Fibonacci hashing.  Simple, fast, but
 *  frequent to collide.
 */

#include <iostream>

uint32_t
mulhash32(uint32_t h, int shift)
{
	return (h * 2654435769u) >> shift;
}

uint64_t
mulhash64(uint64_t h, int shift)
{
	return (h * 11400714819323198485llu) >> shift;
}

int
main()
{
	int shift = 64 - 3;

	// Naively check the distribution.
	std::cout << mulhash32(0, shift) << std::endl;
	std::cout << mulhash32(1, shift) << std::endl;
	std::cout << mulhash32(2, shift) << std::endl;
	std::cout << mulhash32(3, shift) << std::endl;
	std::cout << mulhash32(4, shift) << std::endl;
	std::cout << mulhash32(5, shift) << std::endl;
	std::cout << mulhash32(6, shift) << std::endl;
	std::cout << mulhash32(7, shift) << std::endl;
	std::cout << "---" << std::endl;
	std::cout << mulhash64(0, shift) << std::endl;
	std::cout << mulhash64(1, shift) << std::endl;
	std::cout << mulhash64(2, shift) << std::endl;
	std::cout << mulhash64(3, shift) << std::endl;
	std::cout << mulhash64(4, shift) << std::endl;
	std::cout << mulhash64(5, shift) << std::endl;
	std::cout << mulhash64(6, shift) << std::endl;
	std::cout << mulhash64(7, shift) << std::endl;

	return 0;
}
