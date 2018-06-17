/**
 *  Multiplicative hashing
 *  ======================
 *
 *  Based on the golden ratio, hence A.K.A. Fibonacci hashing.  Simple, fast,
 *  but not well evenly-distributed.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <array>

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

#define LEN 8
#define N 64

template <typename T>
void
debug(std::array<T, LEN> arr)
{
	if constexpr (std::is_same_v<T, uint32_t>) {
		std::cout << "mulhash32=";
	} else {
		std::cout << "mulhash64=";
	}

	std::cout << "[";
	for (const auto& a : arr) std::cout << a << ",";
	std::cout << "\b]" << std::endl;
}

int
main()
{
	std::array<uint32_t, LEN> arr32{};
	std::array<uint64_t, LEN> arr64{};

	// Naively check the distribution.

	for (int i = 0; i < N; ++i) ++arr32[mulhash32(i, 32 - 3)];
	debug(arr32);
	for (int i = 0; i < N; ++i) ++arr64[mulhash64(i, 64 - 3)];
	debug(arr64);

	return 0;
}
