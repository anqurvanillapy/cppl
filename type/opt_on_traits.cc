/**
 *  Operations on traits
 *  ====================
 *
 *  Perform operations like conjunction on types.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>

template <typename T, typename... Ts>
std::enable_if_t<std::conjunction_v<std::is_same<T, Ts>...>>
print_pack_size(T, Ts... xs)
{
	std::cout << sizeof...(xs) + 1 << std::endl;
}

int
main()
{
	print_pack_size(1, 2, 3);
	// No such function defined in compile-time:
	// print_pack_size(1, 2, "oops");
	return 0;
}
