/**
 *  Result
 *  ======
 *
 *  Rust's `std::result` in C++17.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <functional>
#include <variant>
#include <optional>
#include <cassert>

template <typename T, typename E>
class result {
public:
	result()    = delete;
	~result()   = default;

	result(const result<T, E>&)             = delete;
	result& operator=(const result<T, E>&)  = delete;
	result(result<T, E>&&)                  = delete;
	result& operator=(result<T, E>&&)       = delete;

	template <bool Ok = true>
	explicit constexpr result(const std::enable_if_t<Ok, T>& v)
		: v_{v}
		, ok_{Ok}
	{
		/* nop */
	}

	template <bool Ok = false>
	explicit constexpr result(const std::enable_if_t<!Ok, E>& e,
							  const std::nullopt_t&)
		: v_{e}
		, ok_{Ok}
	{
		/* nop */
	}

	auto&
	unwrap() const
	{
		if (ok_) {
			return std::get<0>(v_);
		}
		throw err_();
	}

	auto&
	unwrap_err() const
	{
		if (!ok_) {
			return err_();
		}
		throw std::get<0>(v_);
	}

	auto&
	operator*() const
	{
		return unwrap();
	}

	template <typename F>
	result<T, E>
	and_then(F f) const
	{
		try {
			auto v = std::get<0>(v_);
			return f(v);
		} catch (...) {
			auto e = err_();
			return f(e);
		}
	}

	operator bool() const noexcept
	{
		return ok_;
	}
private:
	constexpr auto&
	err_() const noexcept
	{
		if constexpr (same_type_()) {
			return std::get<0>(v_);
		} else {
			return std::get<1>(v_);
		}
	}

	using same_type_ = std::is_same<T, E>;

	typename std::conditional<
		std::is_same_v<T, E>,
		std::variant<T>,
		std::variant<T, E>
	>::type v_;
	const bool ok_;
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
	return result<T, E>(e, std::nullopt);
}

template <typename T, typename E>
constexpr auto
match(const result<T, E>& res) noexcept
{
	return [&] (std::function<void(T)> f, std::function<void(E)> g) {
		if (res) {
			f(res.unwrap());
		} else {
			g(res.unwrap_err());
		}
	};
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

result<std::string, std::string>
bar(bool c)
{
	if (c) {
		return ok<std::string, std::string>("good");
	} else {
		return err<std::string, std::string>("bad");
	}
}

int
main()
{
	auto a = foo(1 + 1 == 2);
	assert(a);
	assert(a.unwrap() == 42);

	auto b = foo(2 + 2 == 5);
	assert(!b);
	assert(b.unwrap_err() == "failed");

	auto c = bar(1);
	assert(c);
	assert(c.unwrap() == "good");

	auto d = bar(0);
	assert(!d);
	assert(d.unwrap_err() == "bad");

	std::cout << "sizeof a: " << sizeof a << std::endl;
	std::cout << "sizeof b: " << sizeof b << std::endl;

	auto e = ok<int, int>(42);
	auto f0 = [] (int v) { return ok<int, int>(v + 1); };
	auto f1 = [] (int v) { return err<int, int>(v - 1); };
	auto ea = e.and_then(f0).and_then(f0);
	auto eb = e.and_then(f1).and_then(f1);
	assert(ea.unwrap() == 44);
	assert(eb.unwrap_err() == 40);

	match(e)(
		[] (int v) { std::cout << v + v << std::endl; },
		[] (int v) { std::cout << v - v << std::endl; }
	);

	return 0;
}
