/**
 *  RAII
 *  ====
 *
 *  In RAII (resource acquisition is initialization), holding a resource is
 *  a class invariant (constraint), and is tied to object lifetime: resource
 *  allocation (acquisition) is done during object creation (specifically
 *  initialization), by the constructor, while resource deallocation
 *  (release) is done during object destruction (specifically finalization),
 *  by the destructor.
 *
 *  Note: This is an example of multithreaded code convention to introduce
 *  RAII. Compile with -std=c++ -lpthread.
 */

#include <iostream>
#include <thread>

class thread_guard {
public:
    // There won't be implicitly a copy-assignment operation.
    explicit thread_guard(std::thread& t) : _t(t) {}

    // Finalization: join() the thread _t, waiting for its finish.
    ~thread_guard()
    {
        // Once join()-ed, it is not joinable.
        if (_t.joinable()) {
            _t.join();
            std::cout << "join()-ed!" << std::endl;
        }
    }

    // Delete the copy constructor and copy-assignment operator, to ensure
    // they're not automatically provided by the compiler.
    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete;
private:
    std::thread& _t;
};

class functor {
public:
    functor(int& i) : foo(i) {}

    void
    operator()()
    {
        // Potential access to dangling reference.
        for (unsigned i = 0; i < 100; ++i) std::cout << i << " ";
    }
private:
    int& foo;
};

void
oops()
{
    int local_state = 0;
    functor my_functor(local_state);
    std::thread my_thread(my_functor);
    thread_guard g(my_thread);

    std::cout << "Oops! The thread should join() now!" << std::endl;
}   // call the destructor of thread_guard, join()-ing the thread

int
main(int argc, const char *argv[])
{
    // Without the guard, it will return while a thread still has access
    // to local variables, which is undefined behaviour.
    oops();

    return 0;
}
