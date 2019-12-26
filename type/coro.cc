/**
 * C++20 coroutine
 * ===============
 *
 * Note: Compile with
 * clang++ -std=c++2a -fcoroutines-ts -pthread -stdlib=libc++
 */

#include <experimental/coroutine>
#include <iostream>
#include <chrono>
#include <functional>
#include <thread>

using namespace std::literals;

using callback_t = std::function<void(int)>;

void AsyncFunc(int arg, callback_t&& cb)
{
    std::thread t{[=]() {
        std::this_thread::sleep_for(1s);
        cb(arg * 2);
    }};
    t.detach();
}

struct Awaitable {
    int arg;
    int result;

    // Coroutine interface.
    bool await_ready() const { return false; }

    // Coroutine interface.
    int await_resume() { return result; }

    // Coroutine interface.
    void await_suspend(std::experimental::coroutine_handle<> co)
    {
        auto f = [=](int val) mutable {
            result = val;
            co.resume();
        };
        AsyncFunc(arg, f);
    }
};

struct Promise {
    // Promise trait.
    struct promise_type {
        // Promise interface.
        auto get_return_object() { return Promise{}; }

        // Promise interface.
        auto initial_suspend()
        {
            return std::experimental::suspend_never();
        }

        // Promise interface.
        auto final_suspend()
        {
            return std::experimental::suspend_never();
        }

        // Promise interface.
        void unhandled_exception() { std::terminate(); }

        // Promise interface.
        void return_void() {}
    };
};

Promise CoroFunc(int arg, callback_t cb)
{
    int ret = co_await Awaitable{arg};
    ret = co_await Awaitable{ret};
    ret = co_await Awaitable{ret};
    cb(ret);
}

int main()
{
    AsyncFunc(42, [](int result) {
        std::cout << "AsyncFunc: " << result << std::endl;
    });

    CoroFunc(42, [](int result) {
        std::cout << "CoroFunc: " << result << std::endl;
    });

    // Yield the main thread to wait for async callback.
    getchar();

    return 0;
}
