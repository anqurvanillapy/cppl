/**
 *  Result
 *  ======
 *
 *  Rust's `std::result` in C++17.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <variant>
#include <optional>

template <typename T, typename E>
class result {
public:
	result()    = delete;
	~result()   = default;

	result(const result<T, E>&)             = delete;
	result& operator=(const result<T, E>&)  = delete;
	result(result<T, E>&&)                  = delete;
	result& operator=(result<T, E>&&)       = delete;

	explicit constexpr result(const T& v)
		: v_{v}
	{
	}

	explicit constexpr result(const E& e)
		: v_{e}
	{
	}

	explicit constexpr result(const E& e, const std::nullopt_t&)
		: v_{e}
	{
	}

	constexpr auto&
	val() const noexcept
	{
		return std::get<T>(v_);
	}

	constexpr auto&
	err() const noexcept
	{
		return std::get<E>(v_);
	}

	operator bool() const noexcept
	{
		return std::get_if<T>(&v_);
	}
private:
	std::variant<T, E> v_;
};

template <typename T, typename E>
constexpr auto
ok(const T& v) noexcept
{
	return result<T, E>(v);
}

template <typename T, typename E>
constexpr auto
err(const E& e) noexcept
{
	return result<T, E>(e);
}

template <typename T, typename E>
constexpr auto
err(const E& e, const std::nullopt_t& nil) noexcept
{
	return result<T, E>(e, nil);
}

result<int, std::string>
foo(bool c)
{
	if (c) {
		return ok<int, std::string>(42);
	} else {
		return err<int, std::string>("failed");
	}
}

int
main()
{
	auto a = foo(42);
	std::cout << std::boolalpha << "a (" << a << ") = ";
	std::cout << a.val() << std::endl;

	auto b = foo(2 + 2 == 5);
	std::cout << std::boolalpha << "b (" << b << ") = ";
	std::cout << b.err() << std::endl;

	return 0;
}
