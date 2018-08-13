/**
 *  Move assignment
 *  ===============
 *
 *  Convenient way of defining overloaded assignment operator for std::move.
 */

#include <iostream>
#include <algorithm>

class foo {
public:
	foo() = delete;

	explicit foo(int i)
		: i_{i}
	{
		/* nop */
	}

	~foo() = default;

	foo(foo&& rhs)
	{
		*this = std::move(rhs);
	}

	foo&
	operator=(foo&& rhs)
	{
		i_ = std::exchange(rhs.i_, 0);
		return *this;
	}

	int
	get() const
	{
		return i_;
	}
private:
	int i_;
};

int
main()
{
	foo a{42}, b{69};
	b = std::move(a);
	std::cout << a.get() << std::endl;
	std::cout << b.get() << std::endl;
	return 0;
}
