/**
 *  Futures in pool
 *  ===============
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <deque>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <future>

using task_t = std::function<void()>;

std::deque<task_t> tasks;
std::mutex mtx;
std::condition_variable cv;

class worker {
public:
    void operator()() { while (true) poll(); }

    static void
    push_back(const task_t& f)
    {
        std::lock_guard<std::mutex> lk(mtx);
        tasks.push_back(f);
        cv.notify_one();
    }

    static task_t
    pop_front()
    {
        std::unique_lock<std::mutex> lk(mtx);
        cv.wait(lk, [&]{ return !tasks.empty(); });
        auto ret = tasks.front();
        tasks.pop_front();
        return ret;
    }

    void
    poll()
    {
        auto t = pop_front();
        t();
    }
};

int
main()
{
    using namespace std::chrono_literals;

    std::vector<std::thread> ts;
    std::promise<void> prom;
    std::future<void> fut = prom.get_future();

    for (int i = 0; i < 4; ++i) {
        ts.push_back(std::thread{worker{}});
    }

    std::this_thread::sleep_for(1s);

    worker::push_back([&]{
        fut.wait();
        std::cout << " world!" << std::endl;
    });

    worker::push_back([&]{
        std::cout << "Hello,";
        prom.set_value();
    });

    for (auto& t : ts) {
        t.join();
    }

    return 0;
}
