/**
 *  Type identity
 *  =============
 *
 *  Note: Compile with -std=c++17.
 */

template <typename T>
struct type_identity {
  using type = T;
};

template <typename T>
using type_identity_t = typename type_identity<T>::type;

template <typename T>
void foo(T, T) {}

template <typename T>
void bar(T, type_identity_t<T>) {}

int
main()
{
    // foo(4.2, 0); // failed
    bar(4.2, 0);
    return 0;
}
