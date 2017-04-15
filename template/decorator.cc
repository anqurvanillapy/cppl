/**
 *  Decorator
 *  =========
 *
 *  Use a decorator to wrap a function, without modifying its internals,
 *  to record its number of being called by others.
 *
 *  Note: Compile with -std=c++11.
 */

#include <iostream>
#include <functional>

template <class> class decorator;

template <class R, class... Args>
class decorator<R(Args ...)> {
public:
    decorator(std::function<R(Args ...)> f)
    : called(0), _f(f) { /* nop */ }

    R
    operator()(Args ... args)
    {
        called++;
        std::cout << "called: " << called << std::endl;
        return _f(args...);
    }
private:
    unsigned called;
    std::function<R(Args ...)> _f;
};

template <class R, class... Args>
decorator<R(Args ...)>
make_decorator(R (*f)(Args ...))
{
    return decorator<R(Args...)>(std::function<R(Args...)>(f));
}

/// Sample function to wrap.
int
squared(int i)
{
    return i * i;
}

int
main(int argc, const char *argv[])
{
    auto foo = make_decorator(squared);
    for (int i; i < 10; ++i) std::cout << foo(i) << std::endl;
    return 0;
}
