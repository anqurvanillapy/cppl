/**
 *  Coroutine TS
 *  ============
 *
 *  Note: Use Clang to compile with -std=c++17 -fcoroutines-ts -stdlib=libc++,
 *  and libc++-dev, libc++abi-dev are needed.
 */

#include <iostream>
#include <experimental/coroutine>

class generator {
public:
    class promise_type;

    using handle_t = std::experimental::coroutine_handle<promise_type>;

    class promise_type {
    public:
        int
        value() const
        {
            return value_;
        }

        auto
        get_return_object()
        {
            return generator{handle_t::from_promise(*this)};
        }

        auto
        initial_suspend() const
        {
            return std::experimental::suspend_always{};
        }

        auto
        final_suspend() const
        {
            return std::experimental::suspend_always{};
        }

        [[ noreturn ]] void
        unhandled_exception() const
        {
            std::terminate();
        }

        void
        return_void()
        {
            /* nop */
        }

        auto
        yield_value(int value)
        {
            value_ = value;
            return std::experimental::suspend_always{};
        }
    private:
        int value_;
    };

    ~generator()
    {
        if (coro_) {
            coro_.destroy();
        }
    }

    generator(const generator&) = delete;
    generator& operator=(const generator&) = delete;

    generator(generator&& rhs)
        : coro_(rhs.coro_)
    {
        *this = std::move(rhs);
    }

    generator&
    operator=(generator&& rhs)
    {
        rhs.coro_ = nullptr;
        return *this;
    }

    int
    value() const
    {
        return coro_.promise().value();
    }

    bool
    move_next()
    {
        return coro_ ? (coro_.resume(), !coro_.done()) : false;
    }
private:
    generator(handle_t h)
        : coro_(h)
    {
        /* nop */
    }

    handle_t coro_;
};

generator
f()
{
    co_yield 1;
    co_yield 2;
}

int
main()
{
    auto g = f();
    while (g.move_next()) {
        std::cout << g.value() << std::endl;
    }
    return 0;
}
