/**
 *  Dependent types
 *  ===============
 *
 *  Yup it's more like a joke, 'cause where is the kind?
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <vector>

template <typename N>
constexpr void
ensure_positive(N n)
{
	static_assert(n > 0);
}

int
main()
{
	auto three_t = std::integral_constant<int, 3>();
	std::vector<int> vec(three_t);
	std::cout << vec.size() << std::endl; // 3
	ensure_positive(three_t);
	return 0;
}
