/**
 *  Member selection
 *  ================
 *
 *  Member variables declared like a bitset.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>

enum class cmd_t : uint32_t {
    A,
    B,
    C,
};

enum class opt_t : uint32_t {
    None,
    A,
    B,
    C,
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

template <cmd_t Cmd> constexpr bool has_opt(opt_t opt) {
    return static_cast<bool>(opt_v(opt & cmd_trait<Cmd>::opts));
}

template <>
struct cmd_trait<cmd_t::A> {
    static constexpr auto opts = opt_t::A;
};

template <>
struct cmd_trait<cmd_t::B> {
    static constexpr auto opts = opt_t::A | opt_t::B;
};

template <>
struct cmd_trait<cmd_t::C> {
    static constexpr auto opts = opt_t::A | opt_t::B | opt_t::C;
};

template <cmd_t Cmd, typename = void>
struct val_t {
    int A;
    int B;
    int C;
};

template <cmd_t Cmd>
struct val_t<Cmd, std::enable_if_t<!has_opt<Cmd>(opt_t::A)>> {

    int B;
    int C;
};

template <cmd_t Cmd>
struct val_t<Cmd, std::enable_if_t<!has_opt<Cmd>(opt_t::B)>> {
    int A;

    int C;
};

template <cmd_t Cmd>
struct val_t<Cmd, std::enable_if_t<!has_opt<Cmd>(opt_t::C)>> {
    int A;
    int B;

};

int main()
{
    val_t<cmd_t::A> val;
    val.A = 42;
    // val.B = 69; // member not found
    // val.C = 666;
    std::cout << val.A << std::endl;
    return 0;
}
