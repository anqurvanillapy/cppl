/**
 * Lambda call-by-value
 * ====================
 *
 * A simple pitfall when using table-driven lambda maps.
 */

#include <iostream>
#include <functional>
#include <unordered_map>

void Func(int key, int value)
{
    static std::unordered_map<int, std::function<void()>> m{
        {1, [value]() { std::cout << value << std::endl; }},
    };
    if (auto it = m.find(key); it != m.end()) {
        it->second();
    }
}

int main()
{
    Func(0, 42);
    Func(1, 42);
    Func(1, 69); // oops
    // Output:
    //   42
    //   42
}
