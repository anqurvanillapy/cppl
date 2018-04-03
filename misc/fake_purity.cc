/**
 *  Fake purity
 *  ===========
 *
 *  A strongly *const* interface with CRTP-based static polymorphism ensures no
 *  purity.
 *
 *  Note: Compile with -std=c++11.
 */

#include <cassert>

int i = 0;

template <typename T>
class pure_io {
public:
	constexpr void
	run_() const __attribute__((const))
	{
		static_cast<T*>(this)->run();
	}
};

class pure_io_impl : public pure_io<pure_io_impl> {
public:
	void
	run()
	{
		++i;
	}
};

int
main()
{
	pure_io_impl io;
	io.run();
	assert(i == 0); // it fails
	return 0;
}
