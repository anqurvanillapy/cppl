/**
 *  Pointer to implementation
 *  =========================
 *
 *  The Pimpl idiom.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <memory>
#include <experimental/propagate_const>

using namespace std::experimental;

// Interface (.h file)
class Struct {
public:
    Struct(int a);
    int get() const;
    void set(int a);
private:
    struct Impl;
    propagate_const<std::unique_ptr<Impl>> pimpl_;
};

// Implementation (.cc file)
class Struct::Impl {
public:
    explicit Impl(int a) : a_{a} {}

    int get() const { return a_; }
    void set(int a) { a_ = a; }
private:
    int a_;
};

int Struct::get() const { return pimpl_->get(); }
void Struct::set(int a) { pimpl_->set(a); }
Struct::Struct(int a) : pimpl_{std::make_unique<Impl>(a)} {}

int main()
{
    Struct x{42};
    x.set(69);
    std::cout << x.get() << std::endl;

    const Struct y{42};
    // y.set(69); // -fpermissive
    std::cout << y.get() << std::endl;

    return 0;
}
