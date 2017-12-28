/**
 *  constexpr
 *  =========
 *
 *  How good is constexpr?
 *
 *  Note: Compile with -std=c++17 -O3.
 */

#include <cstdio>

constexpr int
factorial(int n)
{
	return n <= 1 ? 1 : (n * factorial(n - 1));
}

constexpr int
fibonacci(int n)
{
	return n <= 1 ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

int
main()
{
	printf("%d\n", factorial(10));
	printf("%d\n", fibonacci(20));
	// Only one procedure (namely `main') in the generated assembly.
	return 0;
}
