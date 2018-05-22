/**
 *  SFINAE
 *  ======
 *
 *  Substitution failure is not an error.
 */

#include <iostream>

class foo0 {
public:
	void
	bar()
	{
		std::cout << ":D" << std::endl;
	}
};

class foo1 {};

template <typename T>
auto
call_if_bar_found(T* t)
	-> decltype(t->bar()) // decltype is necessary
{
	return t->bar();
}

void
call_if_bar_found(...)
{
	std::cout << ":(" << std::endl;
}

int
main()
{
	foo0 x;
	foo1 y;

	call_if_bar_found(&x);
	call_if_bar_found(&y);

	return 0;
}
