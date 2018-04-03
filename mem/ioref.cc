/**
 *  IORef in C++
 *  ============
 *
 *  Very naive attempt.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <functional>
#include <cassert>

int i = 0;

void
foo()
{
	std::cout << "foo" << std::endl;
	++i;
	throw std::runtime_error("");
}

template <typename T, typename ...Args>
class pure_io {
public:
	pure_io(std::function<T(Args...)> fn)
		: fn_{fn}
	{
	}

	void
	run()
	{
		if (p_) fn_();
	}
private:
	constexpr static bool
	p_init_()
	{
		return noexcept(fn_());
	}

	std::function<T(Args...)> fn_;
	constexpr static bool p_ = p_init_();
};

int
main()
{
	pure_io<void> io{foo};
	io.run();
	assert(i == 0);
	return 0;
}
