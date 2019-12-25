/**
 * Rust style <memory>
 * ===================
 *
 * Compile with -std=c++17.
 */

#include <memory>

template <typename T>
using Box = std::unique_ptr<T>;

namespace box {

template <typename T, typename... Args>
auto New(Args &&... args)
{
    if constexpr (std::is_constructible_v<T, Args...>) {
        return Box<T>(new T(std::forward<Args>(args)...));
    } else {
        return Box<T>(new T{std::forward<Args>(args)...});
    }
}

} // namespace box

template <typename T>
using Arc = std::shared_ptr<T>;

template <typename T>
using Weak = std::weak_ptr<T>;

namespace arc {

template <typename T, typename... Args>
auto New(Args &&... args)
{
    if constexpr (std::is_constructible_v<T, Args...>) {
        return Arc<T>(new T(std::forward<Args>(args)...));
    } else {
        return Arc<T>(new T{std::forward<Args>(args)...});
    }
}

} // namespace arc

template <typename T>
using Ref = std::reference_wrapper<T>;

struct Data { int a; int b; };

int main()
{
    auto a = box::New<Data>(1, 2);
    auto b = std::move(a);
    (void)b;

    auto c = arc::New<Data>(1, 2);
    Weak<Data> d = c;
    (void)d;

    Data e{1, 2};
    Ref<Data> f = std::ref(e);
    (void)f;

    return 0;
}
