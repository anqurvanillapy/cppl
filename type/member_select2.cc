/**
 *  Member selection
 *  ================
 *
 *  Member variables declared like a bitset.  Mixins FTW!
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>

enum class cmd_t : uint32_t {
    A,
    B,
};

struct A_t { int A; };
struct B_t { int B; };

template <typename ...Ts>
struct val_t : Ts... {};

template <cmd_t Cmd>
struct cmd_trait {
    using value_type = val_t<>;
};

template <>
struct cmd_trait<cmd_t::A> {
    using value_type = val_t<A_t>;
};

template <>
struct cmd_trait<cmd_t::B> {
    using value_type = val_t<A_t, B_t>;
};

int main()
{
    typename cmd_trait<cmd_t::A>::value_type val;
    val.A = 42;
    // val.B = 69; // member not found
    std::cout << val.A << std::endl;
    return 0;
}
