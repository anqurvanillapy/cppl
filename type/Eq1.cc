/**
 * Alternative version of Eq.cc, shout out to my friend goldimax.
 */

template <typename A, A x, A y>
struct Eq { Eq() = delete; };

template <typename A, A x>
struct Eq<A, x, x> {};

auto _1 = Eq<int, 1, 1>{};
// auto _2 = Eq<int, 1, 2>{}; // compile error

int main() {}
