/**
 *  Pimpl & Go interface
 *  ====================
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <memory>
#include <experimental/propagate_const>

using namespace std::experimental;

#define FEATURE 1

class Interface {
public:
    void foo() const;
    void foo();
private:
    struct Impl;
    propagate_const<std::unique_ptr<Impl>> pimpl_;
};

#if (FEATURE == 1)
struct Interface::Impl {
    void foo() const { std::cout << "(1) const foo\n"; }
    void foo()       { std::cout << "(1) foo\n"; }
};
#elif (FEATURE == 2)
struct Interface::Impl {
    void foo() const { std::cout << "(2) const foo\n"; }
    void foo()       { std::cout << "(2) foo\n"; }
};
#else
    // No implementation: Incomplete type Impl.
#endif

void Interface::foo() const { pimpl_->foo(); }
void Interface::foo()       { pimpl_->foo(); }

int main()
{
    Interface x;
    x.foo();

    const Interface y;
    y.foo();

    return 0;
}
