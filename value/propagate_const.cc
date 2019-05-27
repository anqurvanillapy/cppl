/**
 *  propagate_const
 *  ===============
 *
 *  A const-propagating wrapper for pointers and pointer-like objects.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <memory>
#include <experimental/propagate_const>

using namespace std::experimental;

struct Foo {
    void foo() const { std::cout << "const foo()\n"; }
    void foo() { std::cout << "foo()\n"; }
};

struct Bar {
    Bar() : p_{std::make_unique<Foo>()} {}

    void bar() const
    {
        std::cout << "const bar()\n";
        p_->foo();
    }

    void bar()
    {
        std::cout << "bar()\n";
        p_->foo();
    }

    propagate_const<std::unique_ptr<Foo>> p_;
};

int main()
{
    Bar a;
    a.bar();

    const Bar b;
    b.bar();

    return 0;
}
