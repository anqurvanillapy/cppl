/**
 *  Release-Acquire
 *  ===============
 *
 *  An example of Releasing-Acquire ordering.
 */

#include <iostream>
#include <thread>
#include <atomic>
#include <cassert>

std::atomic<int *> foo;
int bar;

void
producer()
{
    int *p = new int(420);
    bar = 42;

    // Any read-write operations before this write should not be reordered.
    foo.store(p, std::memory_order_release);
}

void
consumer()
{
    int *p;

    while ( !(p = foo.load(std::memory_order_acquire)));

    // These assertions never fire because they are visible for the changes
    // of foo and bar, due to memory_order_release.
    assert(*p == 420);
    assert(bar == 42);
}

int
main(int argc, const char *argv[])
{
    std::thread t1{producer};
    std::thread t2{consumer};
    t1.join(); t2.join();

    return 0;
}
