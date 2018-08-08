/**
 *  Type punning
 *  ============
 *
 *  Welcome to the hell of type punning, strict aliasing and optimization.
 */

#include <iostream>

bool
is_neg(float n)
{
	// Pointer aliasing is sometimes dangerous, but mostly harmful for
	// optimization.  According to strict pointer aliasing rule, the compiler
	// could keep values stored in registers without additional memory I/O.

	// unsigned* u = (unsigned*)(&n);
	// return *u & 0x80000000;
 
	// unsigned* u = reinterpret_cast<unsigned*>(&n);
	// return *u & 0x80000000;

	// Use union for good reinterpret casting.
	union { float x; unsigned y; } u = { .x = n }; // since C++20, tho
	return u.y & 0x80000000; // IEEE 754
}

int
main()
{
	std::cout
		<< std::boolalpha
		<< is_neg(42)
		<< std::endl
		<< is_neg(-42)
		<< std::endl;
	return 0;
}
