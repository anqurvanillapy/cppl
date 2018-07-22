/**
 *  Chain call
 *  ==========
 *
 *  PPL-like `then` method.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <functional>

template <typename T>
class chain_call;

template <typename R, typename... Args>
class chain_call<R(Args...)> {
public:
	chain_call() = delete;

	chain_call(std::function<R(Args...)> f)
		: f_{std::move(f)}
	{
		/* nop */
	}

	~chain_call() = default;

	R
	run(Args&&... args)
	{
		return f_(std::forward<Args>(args)...);
	}

	template <typename F>
	auto
	then(F f)
	{
		auto next = [this, &f](Args&&... args) {
			return f(f_(std::forward<Args>(args)...));
		};
		return chain_call<std::invoke_result_t<F, R>(Args...)>(next);
	}
private:
	std::function<R(Args...)> f_;
};

int
main()
{
	auto f = chain_call<int(int)>([](int i) -> int { return i; });
	auto ret = f
		.then([](int i) { return i + 42; })
		.then([](int i) { return i + 69; })
		.run(0);
	std::cout << ret << std::endl;
	return 0;
}
