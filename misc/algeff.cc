/**
 * Algebraic effects
 * =================
 *
 * Compile with -std=c++17.
 */

#include <functional>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

template <typename T>
struct TypeIdentityHelper {
    using type = T;
};

template <typename T>
using TypeIdentity = typename TypeIdentityHelper<T>::type;

template <typename T>
struct FnTraits : public FnTraits<decltype(&T::operator())> {
};

template <typename T, typename R, typename... Args>
struct FnTraits<R (T::*)(Args...) const> {
    static constexpr auto arity = sizeof...(Args);

    using result_type = R;

    template <size_t i>
    struct arg {
        using type = typename std::tuple_element_t<i, std::tuple<Args...>>;
    };

    template <size_t i>
    using arg_t = typename arg<i>::type;
};

template <typename T, typename U>
class Context final {
  public:
    static std::vector<std::function<T(U)>> &
    Provide(std::function<T(U)> handler)
    {
        g_stk.emplace_back(handler);
        return g_stk;
    }

    static std::optional<T>
    Require(U arg)
    {
        if (g_stk.empty()) {
            return {};
        }
        const auto &fn = g_stk.back();
        return fn(arg);
    }

  private:
    static std::vector<std::function<T(U)>> g_stk;
};

template <typename T, typename U>
std::vector<std::function<T(U)>> Context<T, U>::g_stk{};

template <typename T>
class StackGuard final {
  public:
    StackGuard(std::vector<T> &src)
        : stk_{src}
        , depth_{src.size()}
    {
    }

    StackGuard(std::vector<T> &&src) = delete;

    ~StackGuard()
    {
        if (depth_ == stk_.size()) {
            stk_.pop_back();
        }
    }

    StackGuard &operator=(const StackGuard &) = delete;
    StackGuard(const StackGuard &) = delete;

    StackGuard &operator=(StackGuard &&) = delete;
    StackGuard(StackGuard &&) = delete;

  private:
    std::vector<T> &stk_;
    size_t depth_;
};

#define PROVIDE(handler) \
    auto __h##__LINE__ = (handler); \
    StackGuard __stackGuard##__LINE__( \
        Context< \
            FnTraits<decltype(__h##__LINE__)>::result_type, \
            FnTraits<decltype(__h##__LINE__)>::arg_t<0> \
        >::Provide(std::move(__h##__LINE__)))

#define REQUIRE(T, name) Context<T, TypeIdentity<T>>::Require(name)

struct User {
    std::string name;
    std::vector<std::string> friendNames;
};

std::string GetName(User user)
{
    if (user.name == "") {
        if (auto v = REQUIRE(std::string, "ask_name")) {
            return *v;
        }
        return "";
    }
    return user.name;
}

void MakeFriends(User &user1, User &user2)
{
    user1.friendNames.emplace_back(GetName(user2));
    user2.friendNames.emplace_back(GetName(user1));
}

int main()
{
    User foo{};
    User bar{"Bar", {}};

    PROVIDE([&](std::string effect) -> std::string {
        if (effect == "ask_name") {
            return "Foo";
        }
        return "";
    });

    MakeFriends(foo, bar);

    std::cout << foo.friendNames[0] << std::endl;
    std::cout << bar.friendNames[0] << std::endl;

    return 0;
}
