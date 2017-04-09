/**
 *  DCLP
 *  ====
 *
 *  DCLP (double-checked locking pattern) is a case study of lock-free
 *  programming.
 *
 *  The following class is a singleton that uses the DCLP idiom with acquiring
 *  and releasing fences. The DCLP is such a way of lazy initialization where
 *  the instance is created when the static method is first invoked.
 *
 *  Note: Compile with -std=c++11.
 */

#include <iostream>
#include <mutex>
#include <atomic>

class cargo {
public:
    static cargo*
    get_instance()
    {
        cargo* tmp = instance.load(std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_acquire);

/* Visible area by sync (start) */

        // NULL contains nullptr, actually.
        if (tmp == nullptr) {
            std::lock_guard<std::mutex> lock(mutex);
            tmp = instance.load(std::memory_order_relaxed);

            // Only the first thread will create the singleton.
            if (tmp == nullptr) {
                tmp = new cargo;
                std::atomic_thread_fence(std::memory_order_release);

/* Visible area by sync (end) */

                instance.store(tmp, std::memory_order_relaxed);
            }
        }

        return tmp;
    }

    cargo(const cargo&) = delete;
    void operator=(const cargo&) = delete;
private:
    cargo()
    {
        std::cout << "Finally free from double-checked-locked prison!"
            << std::endl;
    }

    static std::atomic<cargo*> instance;
    static std::mutex mutex;
};

/// The static variables are general (static) to the class, so when using
/// it in another file it is necessary to redeclare it.
std::atomic<cargo*> cargo::instance;
std::mutex cargo::mutex;

int
main(int argc, const char *argv[])
{
    std::cout << cargo::get_instance() << std::endl;
    std::cout << cargo::get_instance() << std::endl;
    return 0;
}
