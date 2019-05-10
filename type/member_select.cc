/**
 *  Member selection
 *  ================
 *
 *  Member variables declared like a bitset.  F**k you SFINAE.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>

enum class cmd_t : uint32_t {
    A,
    B,
};

// NOTE: 4 options => 2^4 (=16) specialized templates.

enum class opt_t : uint32_t {
    None,
    A = 1,
    B = 1 << 1,
};

constexpr uint32_t opt_v(opt_t opt) {
    return std::underlying_type_t<opt_t>(opt);
}

constexpr opt_t operator|(opt_t lhs, opt_t rhs) {
    return static_cast<opt_t>(opt_v(lhs) | opt_v(rhs));
}

constexpr opt_t operator&(opt_t lhs, opt_t rhs) {
    return static_cast<opt_t>(opt_v(rhs) & opt_v(lhs));
}

template <cmd_t Cmd>
struct cmd_trait {
    static constexpr auto opts = opt_t::None;
};

template <cmd_t Cmd> constexpr bool is_opt(opt_t opt) {
    return opt == cmd_trait<Cmd>::opts;
}

template <>
struct cmd_trait<cmd_t::A> {
    static constexpr auto opts = opt_t::A;
};

template <>
struct cmd_trait<cmd_t::B> {
    static constexpr auto opts = opt_t::A | opt_t::B;
};

template <cmd_t Cmd, typename = void>
struct val_t {};

template <cmd_t Cmd>
struct val_t<Cmd, std::enable_if_t<is_opt<Cmd>(opt_t::A)>> {
    int A;
};

template <cmd_t Cmd>
struct val_t<Cmd, std::enable_if_t<is_opt<Cmd>(opt_t::B)>> {
    int B;
};

template <cmd_t Cmd>
struct val_t<Cmd, std::enable_if_t<is_opt<Cmd>(opt_t::A | opt_t::B)>> {
    int A;
    int B;
};

int main()
{
    val_t<cmd_t::A> val;
    val.A = 42;
    // val.B = 69; // member not found
    std::cout << val.A << std::endl;
    return 0;
}
