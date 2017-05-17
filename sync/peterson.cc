/**
 *  Peterson's
 *  ==========
 *
 *  An exercise of Peterson's algorithm of handmaking a mutual exclusion.
 *
 *  Note: Compile with -lpthread.
 */

#include <iostream>
#include <thread>
#include <cassert>

int count = 0;
bool flags[] = { false, false };
int turn = 0;

/// Not thread-safe incrementing for notes.
void
badinc(int m, int *n)
{
    for (int i = 0; i < m; ++i) ++*n;
}

void
inc1(int m, int *n)
{
    for (int i = 0; i < m; ++i) {
        flags[0] = true; turn = 1;
        while (flags[1] == true && turn == 1) { /* busy waiting */ }
        ++*n;    // critical section
        flags[0] = false;
    }
}

void
inc2(int m, int *n)
{
    for (int i = 0; i < m; ++i) {
        flags[1] = true; turn = 0;
        while (flags[0] == true && turn == 0) { /* busy waiting */ }
        ++*n;    // critical section
        flags[1] = false;
    }
}

int
main(int argc, const char *argv[])
{
    // Not thread-safe.
    std::thread bad1{badinc, 1000, &count};
    std::thread bad2{badinc, 1000, &count};
    bad1.join(); bad2.join();
    // Sometimes 2000 though...
    std::cout << "count=" << count << std::endl;

    // Thread-safe, perhaps.
    count = 0;
    std::thread safe1{inc1, 1000, &count};
    std::thread safe2{inc2, 1000, &count};
    safe1.join(); safe2.join();
    // Sometimes NOT 2000 though...
    std::cout << "count=" << count << std::endl;

    // XXX: Okay, it goes nuts.
    count = 0;
    std::thread noway1{inc1, 1000000, &count};
    std::thread noway2{inc2, 1000000, &count};
    noway1.join(); noway2.join();
    std::cout << "count=" << count << std::endl;

    return 0;
}
