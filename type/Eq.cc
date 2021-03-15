/**
 * Eh, do some theorem proving in C++, why not.
 *
 * > -std=c++2a -O2 -Wall -Wextra -pedantic -pthread
 *
 * Make sure you have a compiler that could serve non-primitive types as
 * non-type template parameters!!!
 */

// let Eq : {A : U} → A → A → U
// = λ {A} x y. (P : A → U) → P x → P y;
template <typename A, A x, A y>
struct Eq {
    template <template <A> typename P, P<x>>
    struct t {
        static constexpr P<y> v{}; 
    };
};

// let refl : {A : U}{x : A} → Eq {A} x x
// = λ _ px. px;
template <typename A, A x>
struct refl {
    template <template <A> typename P, P<x> px>
    static constexpr typename Eq<A, x, x>::template t<P, px> v{};
};

// let the : (A : U) → A → A = λ _ x. x;
template <typename A, A x>
struct the {
    static constexpr A v = x;
};

// the (Eq (int 1 1)) refl
template <template <int> typename P, P<1> p>
auto _1 = the<
    Eq<int, 1, 1>::t<P, p>,
    refl<int, 1>::v<P, p>
>{};
template <int> struct _2 {};
auto _3 = _1<_2, _2<1>{}>;

int main() {}
