/**
 * Monad
 * =====
 *
 * Monad is just a monoid in the endofunctor category, what's the problem?
 *
 * The following code might be wrong actually ;)
 */

#include <functional>

#define 𝓒 typename

template <𝓒> struct Applicative {
  template <𝓒 𝕏, 𝓒 𝕐> static Applicative<𝕐(𝕏)> Pure(std::function<𝕐(𝕏)> x);

  template <𝓒 𝕏, 𝓒 𝕐>
  static Applicative<𝕐> Seq(Applicative<𝕏> a, Applicative<𝕐(𝕏)> f);
};

template <𝓒 𝔸> struct Monad : Applicative<𝔸> {
  template <𝓒 𝕏> static Monad<𝕏> Return(𝕏 x);
  template <𝓒 𝕏> static Monad<𝕏> μ(Monad<Monad<𝕏>> x);

  template <𝓒 𝕏, 𝓒 𝕐, 𝓒 ℤ>
  static std::function<Monad<ℤ>(𝕏)> ￮(std::function<Monad<ℤ(𝕐)>> g,
                                      std::function<Monad<𝕐(𝕏)>> f) {
    return [=](𝕏 x) { return μ(Seq(f(x), Pure(g))); };
  }
};

int main() {}
