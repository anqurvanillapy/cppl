/**
 *  new
 *  ===
 */

#include <iostream>
#define UNUSED(x) ((void)x)

class foo {
public:
	foo()
		: x_(new int)
	{
		/* nop */
	}

	~foo()
	{
		std::cout << "foo dtor" << std::endl;
		delete x_;
	}
private:
	int* x_;    // 4B leaks
};

int
main()
{
	char* a = new char[sizeof(foo)];
	foo* b = new(a) foo;    // with placement_params
	// b->~foo();
	UNUSED(b);
	delete[] a;

	return 0;
}
