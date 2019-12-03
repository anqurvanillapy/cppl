/**
 * Newtype in C++
 * ==============
 *
 * Note: Compile with -std=c++17.
 */

#include <iostream>

namespace details {

template <typename T, typename U>
struct phantom_type
{
    explicit constexpr phantom_type(T const& v) : value(v) {}
    explicit constexpr phantom_type(T&& v) : value(std::move(v)) {}
    operator T& () noexcept { return value; }
    constexpr operator T const& () const noexcept { return value; }

    constexpr bool operator==(const phantom_type& rhs) const {return value == rhs.value;}
    constexpr bool operator<(const phantom_type& rhs) const {return value < rhs.value;}

    T value;
};

} /* namespace details */

#define NEWTYPE(TYPE_NAME, BASE_TYPE) \
struct TYPE_NAME : details::phantom_type<BASE_TYPE, TYPE_NAME> \
{ \
    using phantom_type::phantom_type; \
}

NEWTYPE(Id, uint32_t);

void Print(Id data)
{
    std::cout << "Id: " << data << std::endl;
}

int main()
{
    // Size of a primitive type.
    static_assert(sizeof(Id) == 4);

    Id a{42};
    Id b{69};

    // Guarantee to pass the primitive using %edi.
    Print(a);
    std::cout << std::boolalpha << (a < b) << std::endl;

    return 0;
}
