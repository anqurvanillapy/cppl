/**
 *  shared_ptr
 *  ==========
 *
 *  A stack-allocated object that wraps a pointer so that users don't have
 *  to know who owns it.  When the last shared pointer for an object in
 *  memory is destructed, the wrapped pointer will also be deleted.
 *
 *  Note: Compile with -lpthread and -std=c++11. The results might be wrong
 *  especially the use_count(), which could vary from C++ standards and
 *  different versions of GCC/Clang.
 */

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

struct Foo {
    Foo() { std::cout << "Foo::Foo()" << std::endl; }
    ~Foo() { std::cout << "Foo::~Foo()" << std::endl; }
};

struct Bar : public Foo {
    Bar() { std::cout << "Bar::Bar()" << std::endl; }
    ~Bar() { std::cout << "Bar::~Bar()" << std::endl; }
};

void
thread_func(std::shared_ptr<Foo> p)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::shared_ptr<Foo> lp = p;    // local pointer, whose use_count could
                                    // be incremented atomically
    // Local variables for lock/unlock.
    {
        static std::mutex io_mutex;
        std::lock_guard<std::mutex> lk(io_mutex);
        std::cout << "* Local pointer in a thread:" << std::endl
                  << "    lp.get(): " << lp.get()
                  << ", lp.use_count(): " << lp.use_count() << std::endl;
    }
}

int
main(int argc, const char *argv[])
{
    // Notes that p here cannot access Bar's members.
    std::shared_ptr<Foo> p = std::make_shared<Bar>();

    std::cout << "main() creates a shared Bar" << std::endl
              << "  p.get(): " << p.get()
              << ", p.use_count(): " << p.use_count() << std::endl;

    std::thread t1(thread_func, p), t2(thread_func, p), t3(thread_func, p);
    p.reset();  // release ownership from main

    std::cout << "main() releases ownership of Bar" << std::endl
              << "  p.get(): " << p.get()
              << ", p.use_count(): " << p.use_count() << std::endl;

    t1.join(); t2.join(); t3.join();
    std::cout << "The last thread completes and deletes Bar" << std::endl;

    return 0;
}
