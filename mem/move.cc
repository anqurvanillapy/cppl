/**
 *  std::move
 *  =========
 *
 *  Some insights of std::move().
 */

#include <iostream>

class X {
public:
    X() { /* nop */ }
    explicit X(int i) : a(i), b(new int{i}) { /* nop */  }
    ~X() { if (*b) delete b; /* no possible leaks now */ }

    X(const X&) = delete;
    void operator=(const X&) = delete;

    X(X&& x) { *this = std::move(x); }
    X& operator=(X&& x)
    {
        a = x.a;
        b = x.b;
        return *this;
    }

    int a;
    int *b;
};

void
steal(X& x)
{
    X temp = std::move(x);
    std::cout << "(steal) ";
    std::cout << &temp << ": a=" << temp.a << ",b=" << *temp.b << std::endl;
    std::cout << &x << ": a=" << x.a << ",b=" << *x.b << std::endl;
    // So std::move just indicates that the ownership has been transferred,
    // unlike Rust whose compiler can detect the real ownership transferring
    // by a borrow checker at compile-time.
}

int
main(int argc, const char *argv[])
{
    X foo{42};
    steal(foo);
    // foo.b is now 0 since X::~X() is triggered after steal.
    std::cout << &foo << ": a=" << foo.a << ",b=" << *foo.b;
    std::cout << " (foo dealloc'd to prevent mem leak)" << std::endl;
    return 0;
}
