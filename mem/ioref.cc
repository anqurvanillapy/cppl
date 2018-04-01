/**
 *  IORef in C++
 *  ============
 *
 *  Very naive attempt.
 *
 *  Note: Compile with -std=c++17.
 */

#include <functional>
#include <cassert>

int i = 0;

template <typename T>
class pure_io {
public:
	constexpr static int
	foo()
	{
		return 42;
	}
private:
	constexpr static T v_ = foo();
};

int
main()
{
	return 0;
}
