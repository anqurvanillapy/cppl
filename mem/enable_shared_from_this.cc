/**
 *  enable_shared_from_this
 *  =======================
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <memory>

struct Good : public std::enable_shared_from_this<Good> {
    std::shared_ptr<Good> getptr()
    {
        return shared_from_this();
    }
};

struct Bad {
    ~Bad() { std::cout << "Bad::~Bad()\n"; }

    std::shared_ptr<Bad> getptr()
    {
        return std::shared_ptr<Bad>(this);
    }
};

int main()
{
    std::shared_ptr<Good> p1 = std::make_shared<Good>();
    std::shared_ptr<Good> p2 = p1->getptr();
    std::cout << "p2.use_count()=" << p2.use_count() << std::endl;

    try {
        Good not_good_tho;
        std::shared_ptr<Good> p3 = not_good_tho.getptr();
    } catch (std::bad_weak_ptr& e) {
        // Thrown since C++17.
        std::cout << e.what() << std::endl;
    }

    std::shared_ptr<Bad> p4 = std::make_shared<Bad>();
    std::shared_ptr<Bad> p5 = p4->getptr();
    std::cout << "p5.use_count()=" << p5.use_count() << std::endl;

    // UB: double-delete of Bad.
    // Output:
    //   double free or corruption
}
