/**
 *  Promise
 *  =======
 *
 *  An example of how std::promise can be used as signals between threads with
 *  its associated shared states.
 *
 *  Note: Compile with -pthread -std=c++11.
 */

#include <future>
#include <thread>
#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>

void
sum(std::vector<int>::iterator first,
    std::vector<int>::iterator last,
    std::promise<int> p)
{
    int sum = std::accumulate(first, last, 0);
    p.set_value(sum);
}

void
think(std::promise<void> p)
{
    std::cout << "I'm thinking..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    p.set_value();  // like ES6's resolve()
}

int
main(int argc, const char *argv[])
{
    /* Transmit a result between threads. */
    std::vector<int> nums = { 1, 2, 3 };    // copy initialization
    std::promise<int> sum_promise;
    std::future<int> sum_future = sum_promise.get_future();

    std::thread t1(sum, nums.begin(), nums.end(),
                   std::move(sum_promise));  // instead of copy

    sum_future.wait();  // wait for results
    std::cout << "result=" << sum_future.get() << std::endl;
    t1.join();   // wait for thread completion

    /* Signal a state between threads. */
    std::promise<void> think_promise;
    std::future<void> think_future = think_promise.get_future();

    std::thread t2(think, std::move(think_promise));

    think_future.wait();
    std::cout << "Dinner time!" << std::endl;
    t2.join();

    return 0;
}
