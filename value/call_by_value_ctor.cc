/**
 *  Call-by-value & ctor
 *  ====================
 *
 *  Call-by-value function calls will not trigger the constructor after copying,
 *  only member variables concerned.
 */

#include <iostream>

class foo {
public:
	foo()
	{
		std::cout << "foo ctor" << std::endl;
	}
};

void
call_by_value(foo x)
{
	(void)x;
}

int
main()
{
	foo x;
	call_by_value(x);
	// foo ctor runs once.

	return 0;
}
