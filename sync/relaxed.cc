/**
 *  Relaxed
 *  =======
 *
 *  Typical use for relaxed memory ordering is incrementing counters.
 *
 *  Note: Compile with -std=c++11 -pthread.
 */

#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

/// Copy-list-initialization.
std::atomic_int cnt = {0};

/// Direct-initialization.
// std::atomic_int cnt{0};

void
inc()
{
    for (int n = 0; n < 42; ++n) cnt.fetch_add(1, std::memory_order_relaxed);
}

int
main(int argc, const char *argv[])
{
    std::vector<std::thread> tv;

    // emplace_back avoids extra copy or move operations required by
    // push_back.
    for (int n = 0; n < 10; ++n) tv.emplace_back(inc);
    for (auto& t : tv) t.join();

    // The final value must be 420.
    std::cout << cnt << std::endl;

    return 0;
}
