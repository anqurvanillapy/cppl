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

    while ( !(p = foo.load(std::memory_order_consume)));

    // Due to data dependency, p depends on the changes of foo, but here it
    // is never visible to see the changes of bar, so the first assertion
    // will never fire, but the second may or may not.
    //
    // Moreover, if heavy compiler strategy of memory_order_consume is used,
    // it is the same to memory_order_acquire, rather an alias.
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
