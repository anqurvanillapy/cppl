/**
 *  Singleton
 *  =========
 *
 *  A cargo-cult-prone singleton, with lazy evaluation and guaranteed
 *  destruction.
 *
 *  Anyway, this could be a case study about achieving thread-safe by
 *  using static variable (if it has to), because this implementation
 *  is safe for concurrent execution. As for DCLP (double-checked locking
 *  pattern), it is included in other discussions. BTW, *singleton
 *  pattern is bad*.
 *
 *  Note: Compile with -std=c++11.
 */

#include <iostream>

class cargo {
public:
    // The following method would trigger the initialization of the
    // instance, and if a static local variable is already being
    // initialized, concurrent execution shall wait in C++.
    static cargo&
    get_instance()
    {
        // The instance is guaranteed to be destroyed and instantiated on
        // first use.
        static cargo instance;
        return instance;
    }

    // Public deleted functions result in better error messages since the
    // compiler would check accessibility before deleted status.
    cargo(cargo const&) = delete;
    void operator=(cargo const&) = delete;
private:
    cargo()
    {
        std::cout << "Hey, it's the earth. I'm unique." << std::endl;
    }
};

int
main(int argc, const char *argv[])
{
    cargo::get_instance();
    return 0;
}
