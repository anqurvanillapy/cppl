/**
 *  Monad
 *  =====
 */

#define 𝓒 typename

template <𝓒> struct 𝕋 {
    template <𝓒 𝕏> 𝕋<𝕏> pure(𝕏 x);
    template <𝓒 𝕏> 𝕋<𝕏> μ(𝕋<𝕋<𝕏>> x);
};

int main(){}
