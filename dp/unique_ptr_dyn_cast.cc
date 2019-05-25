/**
 *  dynamic_cast unique_ptr
 *  =======================
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <memory>

struct Base { virtual ~Base() = default; };
struct DerivedA : public Base {};
struct DerivedB : public Base {};

int main()
{
    std::unique_ptr<Base> x = std::make_unique<DerivedA>();

    if (DerivedB* b = dynamic_cast<DerivedB*>(x.get())) {
        (void)b;
        std::cout << "DerivedB" << std::endl;
    } else if (DerivedA* a = dynamic_cast<DerivedA*>(x.get())) {
        (void)a;
        std::cout << "DerivedA" << std::endl;
    }

    return 0;
}
