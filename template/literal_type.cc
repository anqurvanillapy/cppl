/**
 *  LiteralType
 *  ===========
 *
 *  Literal types are the types of constexpr variables and they can be
 *  constructed, manipulated, and returned from constexpr functions.
 *
 *  The literal types could be embadded in a template to do something in
 *  compile time.
 *
 *  Note: Compile with -std=c++11.
 */

#include <iostream>
#include <stdexcept>

class conststr {
public:
    // Initializes siz and p, if an array of char given.
    template<std::size_t n>
    constexpr conststr(const char(&a)[n]) : p(a), siz(n - 1) { /* nop */ }

    // `\x0' is not allowed to return.
    constexpr char
    operator[](std::size_t n) const
    {
        return n < siz ? p[n] : throw std::out_of_range("");
    }

    // siz getter.
    constexpr std::size_t size() const { return siz; }
private:
    const char *p;      // points to the constant string
    std::size_t siz;    // length of the string
};

constexpr std::size_t
lowercase_cnt(conststr s, std::size_t n = 0, std::size_t cnt = 0)
{
    // Recursively count the lowercase letters.
    return n == s.size() ? cnt :
           s[n] >= 'a' && s[n] <= 'z' ? lowercase_cnt(s, n + 1, cnt + 1) :
                                        lowercase_cnt(s, n + 1, cnt);
}

/// Test the output with a compile-time function.
template<int n>
struct const_N {
    const_N() { std::cout << n; }
};

int
main(int argc, const char *argv[])
{
    std::cout << "\"Hello, world!\" has ";
    // This literal is implicitly converted to conststr.
    const_N<lowercase_cnt("Hello, world!")>();
    std::cout << " lowercase letters" << std::endl;

    return 0;
}
