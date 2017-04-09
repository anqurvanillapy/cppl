/**
 *  Once
 *  ====
 *
 *  Singleton pattern implemented by C++11's call_once, which could be
 *  also achieved by POSIX's pthread_once. Note that initialization of
 *  function-local statics, as mentioned in singleton.cc, is guaranteed
 *  to occur only once even when called from multiple threads, which
 *  might be more efficient.
 *
 *  Note: Compile with -std=c++11 -pthread.
 */

#include <iostream>
#include <mutex>

class cargo {
public:
    static cargo*
    get_instance()
    {
        std::call_once(cargo_flag, [] {
            instance = new cargo;
        });
        return instance;
    }

    cargo(const cargo&) = delete;
    void operator=(const cargo&) = delete;
private:
    cargo()
    {
        std::cout << "YOLO." << std::endl;
    }

    static std::once_flag cargo_flag;
    static cargo *instance;
};

std::once_flag cargo::cargo_flag;
cargo* cargo::instance;

int
main(int argc, const char *argv[])
{
    std::cout << cargo::get_instance() << std::endl;
    std::cout << cargo::get_instance() << std::endl;
    return 0;
}
