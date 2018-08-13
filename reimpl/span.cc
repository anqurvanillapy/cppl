/**
 *  Span
 *  ====
 *
 *  Reference implementation of C++20 std::span.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <cassert>

template <typename T, typename U>
constexpr T
narrow_cast(U&& u)
{
	// For casting to size_t.
	return static_cast<T>(std::forward<U>(u));
}

template <typename T>
class span {
public:
	span() = delete;

	template <typename U, size_t N>
	constexpr span(U(&arr)[N]) noexcept
		: first_{std::addressof(arr[0])}
		, last_{std::addressof(arr[0]) + N}
	{
		/* nop */
	}

	~span() = default;

	constexpr size_t
	size() const noexcept
	{
		return narrow_cast<size_t>(last_ - first_);
	}

	constexpr bool
	empty() const noexcept
	{
		return size() == 0;
	}

	constexpr T&
	at(size_t i) const noexcept
	{
		assert(i < size());
		return first_[i];
	}

	constexpr T&
	operator[](size_t i) const noexcept
	{
		return at(i);
	}
private:
	T* first_;
	T* last_;
};

template <typename T, size_t N>
span(T(&)[N]) -> span<T>;

void
print_tuple(span<int> t)
{
	std::cout << "(" << t[0] << "," << t[1] << "," << t[2] << ")" << std::endl;
	std::cout << t.size() << std::endl;
}

int
main()
{
	int tuple[3] = {1, 2, 3};
	print_tuple(tuple);
	return 0;
}
