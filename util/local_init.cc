/**
 * Local initializer
 * =================
 *
 * Note: Compile with -std=c++17.
 */

#include <iostream>
#include <thread>

#define DEFINE_LOCAL_INITIALIZER(className) \
class className final { \
public: \
    static void Start() \
    { \
        static thread_local className inst; \
    } \
\
private: \
    className()

#define END_LOCAL_INITIALIZER(className) };

DEFINE_LOCAL_INITIALIZER(Foo)
{
    std::cout << "foo\n";
}
END_LOCAL_INITIALIZER(Foo)

int main()
{
    Foo::Start();

    std::thread t{[] { Foo::Start(); }};
    t.join();
}
