/**
 *  uint24_t
 *  ========
 *
 *  A naive implementation of uint24_t that is determined to ignore the
 *  alignment.  It's usually better to use uin32_t for general cases.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>

template <typename T, typename U>
constexpr T
narrow_cast(U&& u) noexcept
{
	return static_cast<T>(std::forward<U>(u));
}

class uint24_t {
public:
	template <typename T>
	constexpr uint24_t(T t) noexcept
	{
		buf_[0] = narrow_cast<uint8_t>(t       );
		buf_[1] = narrow_cast<uint8_t>(t >>  8u);
		buf_[2] = narrow_cast<uint8_t>(t >> 16u);
	}

	constexpr explicit operator int() const
	{
		int ret = 0;
		ret |= buf_[0];
		ret |= buf_[1] >> 8u;
		ret |= buf_[2] >> 16u;
		return ret;
	}
private:
	uint8_t buf_[3] = {0};
};

int
main()
{
	constexpr uint24_t a = 42u;
	std::cout << sizeof a << std::endl;
	std::cout << static_cast<int>(a) << std::endl;
	return 0;
}

