/**
 *  Peterson With Atomics
 *  =====================
 *
 *  Peterson's algorithm should be better when the `flag' and `turn' are able to
 *  be accessed atomically.
 *
 *  - But... why? They are atomics why didn't you just...
 *  - ikr.
 *
 *  Note: Compile with -std=c++11 -lpthread.
 */

#include <iostream>
#include <thread>
#include <atomic>

int count = 0;
std::atomic<bool> flags[2] = {};
std::atomic_int turn;

void
inc1(int m, int *n)
{
    for (int i = 0; i < m; ++i) {
        flags[0].store(true, std::memory_order_relaxed);
        turn.store(1, std::memory_order_relaxed);
        while (flags[1].load(std::memory_order_relaxed) == true
                && turn.load(std::memory_order_relaxed) == 1) {
            /* busy waiting */
        }
        ++*n;
        flags[0].store(false, std::memory_order_relaxed);
    }
}

void
inc2(int m, int *n)
{
    for (int i = 0; i < m; ++i) {
        flags[1].store(true, std::memory_order_relaxed);
        turn.store(0, std::memory_order_relaxed);
        while (flags[0].load(std::memory_order_relaxed) == true
                && turn.load(std::memory_order_relaxed) == 0) {
            /* busy waiting */
        }
        ++*n;
        flags[1].store(false, std::memory_order_relaxed);
    }
}

int
main(int argc, const char *argv[])
{
    std::thread t1{inc1, 1000000, &count};
    std::thread t2{inc2, 1000000, &count};
    t1.join(); t2.join();
    // Yeah it's 2000000 now!
    std::cout << "count=" << count << std::endl;

    return 0;
}
