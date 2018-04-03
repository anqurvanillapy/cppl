/**
 *  `const`-based purity
 *  ====================
 *
 *  Purity ensured by a strongly *const* interface with CRTP-based static
 *  polymorphism.
 *
 *  Note: Compile with -std=c++11.  __attribute__((const)) is not portable and
 *  does no purity checks, leaving no modifications from side effects.
 */

#include <cassert>

int i = 0;

template <typename T>
class pure_io {
public:
	constexpr void
	run() const __attribute__((const))
	{
		static_cast<const T*>(this)->run_impl();
	}
};

class pure_io_impl : public pure_io<pure_io_impl> {
public:
	void
	run_impl() const
	{
		++i;
	}
};

int
main()
{
	pure_io_impl io{};
	io.run();
	assert(i == 0); // no compilation errors and side effects
	return 0;
}
