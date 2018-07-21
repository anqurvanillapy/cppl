/**
 *  `defer`
 *  =======
 *
 *  A simple scope guard, or a `defer` in Go.
 *
 *  Note: Compile with -std=c++17.
 */

#include <utility>
#include <iostream>

template <typename T>
class scope_guard {
public:
	scope_guard() = delete;
	scope_guard(T f)
		: f_{std::move(f)}
		, active_{true}
	{
		/* nop */
	}

	~scope_guard()
	{
		if (active_) {
			f_();
		}
	}

	scope_guard(scope_guard&& rhs)
		: f_{std::move(rhs.f_)}
		, active_{rhs.active_}
	{
		rhs.dismiss();
	}

	scope_guard(const scope_guard&)             = delete;
	scope_guard& operator=(const scope_guard&)  = delete;

	inline void
	dismiss()
	{
		active_ = false;
	}
private:
	T f_;
	bool active_;
};

template <typename T>
auto
defer(T f)
{
	return scope_guard<T>(std::move(f));
}

void
foo()
{
	auto g = defer([] {
		std::cout << "foo exit with exception" << std::endl;
	});
	throw 42;
}

int
main()
{
	auto g = defer([] {
		std::cout << "main exit" << std::endl;
	});

	try {
		foo();
	} catch (...) {
		/* nop */
	}

	return 0;
}
