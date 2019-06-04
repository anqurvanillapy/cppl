/**
 *  std::owner_less
 *  ===============
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <memory>
#include <set>

struct X {};

int main()
{
    X* x = new X();

    std::shared_ptr<X> a(x);
    std::shared_ptr<X> b(x);

    std::set<std::shared_ptr<X>> s1;
    s1.insert(a);
    std::cout << s1.size() << std::endl;
    s1.insert(b);
    std::cout << s1.size() << std::endl;

    std::set<
        std::shared_ptr<X>,
        std::owner_less<std::shared_ptr<X>>
    > s2;
    s2.insert(a);
    std::cout << s2.size() << std::endl;
    s2.insert(b);
    std::cout << s2.size() << std::endl;

    return 0;
}
