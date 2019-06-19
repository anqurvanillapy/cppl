/**
 *  x86 hotpatch
 *  ============
 *
 *  Based on this post: https://nullprogram.com/blog/2016/03/31/.
 *
 *  Note: Compile with -std=c++17 -lpthread.
 */

#include <iostream>
#include <thread>
#include <cassert>

#include <unistd.h>
#include <sys/mman.h>

/**
 * Narrowing cast
 */
template <class T, class U>
constexpr T ncast(U&& u) noexcept
{
    return static_cast<T>(std::forward<U>(u));
}

__attribute__((ms_hook_prologue))
__attribute__((aligned(8)))
__attribute__((noinline))
__attribute__((noclone))
void hello()
{
    __asm__("");
    std::cout << "hello\n";
}

void world()
{
    std::cout << "world\n";
}

void hotpatch(void* target, void* replacement)
{
    int ret;

    // Check alignment.
    assert((reinterpret_cast<uintptr_t>(target) & 0x07) == 0);

    auto page = reinterpret_cast<void *>(
                reinterpret_cast<uintptr_t>(target) & ~0xfff);
    ret = mprotect(page, 4096, PROT_WRITE | PROT_EXEC);
    uint32_t rel = reinterpret_cast<char *>(replacement) -
                   reinterpret_cast<char *>(target) - 5;
    if (ret != 0) {
        std::cerr << "mprotect W^X error\n";
        return;
    }

    static union {
        uint8_t bytes[8];
        uint64_t value;
    } instruction = {{
        0xe9,
        ncast<uint8_t>(rel >> 0),
        ncast<uint8_t>(rel >> 8),
        ncast<uint8_t>(rel >> 16),
        ncast<uint8_t>(rel >> 24)
    }};
    *reinterpret_cast<uint64_t *>(target) = instruction.value;
    ret = mprotect(page, 4096, PROT_EXEC);
    if (ret != 0) {
        std::cerr << "mprotect X error\n";
    }
}

int main()
{
    std::thread t([]{
        while (true) {
            hello();
            usleep(100000);
        }
    });
    std::getchar();
    hotpatch(reinterpret_cast<void *>(hello),
             reinterpret_cast<void *>(world));
    t.join();
    return 0;
}
