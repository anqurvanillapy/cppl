/**
 *  unique_ptr reference in std::variant
 *  ====================================
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <memory>
#include <variant>

struct X { int data; };

class Foo {
public:
    Foo() : n_{std::make_unique<X>()}
    {
        n_->data = 42;
    }

    using val_ref_t = std::reference_wrapper<std::unique_ptr<X>>;

    std::variant<val_ref_t, std::string> get(bool ok) {
        if (ok) {
            return std::ref(n_);
        }
        return "failed";
    }
private:
    std::unique_ptr<X> n_;
};

int main()
{
    Foo foo;
    auto a = foo.get(true);
    std::cout << std::get<0>(a).get()->data << std::endl;
    std::cout << a.index() << std::endl;

    auto b = foo.get(false);
    std::cerr << std::get<1>(b) << std::endl;
    std::cout << b.index() << std::endl;

    return 0;
}
