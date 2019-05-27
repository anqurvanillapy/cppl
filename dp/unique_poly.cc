/**
 *  unique_ptr polymorphism
 *  =======================
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <memory>

struct Base { virtual ~Base() = default; };
struct A : public Base { int a; };
struct B : public Base { double b; };

void func(std::unique_ptr<Base> base)
{
    std::shared_ptr<Base> p = std::move(base);
    auto a = std::static_pointer_cast<A>(std::move(p));
    std::cout << a->a << std::endl;
}

int main()
{
    auto p = new A;
    p->a = 42;
    std::unique_ptr<Base> a{p};
    func(std::move(a));
    return 0;
}
