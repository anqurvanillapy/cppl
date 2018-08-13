/**
 *  Move wrapper
 *  ============
 *
 *  A dead simple wrapper for checking use-after-move error with `std::move`.
 *  Note that an object could be re-constructed after being std::moved.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <cassert>

#define UNLIKELY(c) __builtin_expect(static_cast<bool>(c), false)

template <typename T>
class mvwrap {
public:
	mvwrap() = default;

	mvwrap(T t)
		: t_{t}
		, moved_{false}
	{
		/* nop */
	}

	~mvwrap() = default;

	mvwrap(const mvwrap<T>&) = delete;
	mvwrap& operator=(const mvwrap<T>&) = delete;

	mvwrap(mvwrap<T>&& rhs)
	{
		*this = std::move(rhs);
	}

	mvwrap<T>&
	operator=(mvwrap<T>&& rhs)
	{
		t_ = rhs.t_;
		rhs.~mvwrap();
		rhs.moved_ = true;
		moved_ = false;
		return *this;
	}

	T&
	operator*()
	{
		if (UNLIKELY(moved_)) {
			assert(false);
		}
		return t_;
	}
private:
	T t_;
	bool moved_;
};

class foo {
public:
	foo() = default;

	foo(int n)
		: n_{n}
	{
		/* nop */
	}

	~foo() = default;

	auto
	get() const
	{
		return n_;
	}
private:
	int n_;
};

int
main()
{
	mvwrap<foo> a = {42};
	std::cout << (*a).get() << std::endl;
	mvwrap<foo> b = std::move(a);
	// std::cout << (*a).get() << std::endl; // oops
	a = {69};
	std::cout << (*a).get() << std::endl;
	return 0;
}
