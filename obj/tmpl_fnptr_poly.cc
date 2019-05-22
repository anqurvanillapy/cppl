/**
 *  Polymorphism with template and function pointer
 *  ===============================================
 */

#include <iostream>

class Foo {
public:
    template <typename T>
    struct InternalT {
        static int (*id)(int);
    };

    typedef InternalT<void> Internal;

    void func() {
        std::cout << Internal::id(42) << std::endl;
    }
};

template <typename T>
int (*Foo::InternalT<T>::id)(int) = [](int a) { return a; };

int main()
{
    Foo a;
    a.func();
    Foo::Internal::id = [](int a) { return a * 2; };
    a.func();
    return 0;
}
