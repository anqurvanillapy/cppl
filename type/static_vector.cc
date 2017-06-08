/**
 *  Static vector
 *  =============
 *
 *  A static vector implemented by using std::aligned_storage, with which, for
 *  instance, a user can avoid using something like static/dynamic char array to
 *  do the placement construction.
 *
 *  Note: Compile with -std=c++11.
 */

#include <iostream>
#include <type_traits>

template <typename T, size_t N>
class static_vector {
public:
    static_vector() = default;

    ~static_vector()
    {
        for (size_t pos = 0; pos < siz_; ++pos) {
            reinterpret_cast<T*>(data_ + pos)->~T();
        }
    }

    // No copy and move.
    static_vector(const static_vector&) = delete;
    static_vector& operator=(const static_vector&) = delete;
    static_vector(static_vector&&) = delete;
    static_vector& operator=(static_vector&&) = delete;

    // Create an object in aligned storage (in place).
    template <typename ...Args>
    void
    emplace_back(Args&&... args)
    {
        if (siz_ >= N) throw std::bad_alloc{};
        ::new(data_ + siz_) T(std::forward<Args>(args)...);
        ++siz_;
    }

    // Accessing.
    const T&
    operator[](size_t pos) const
    {
        // Without compiling any CPU instructions, it is purely a compiler
        // directive which instructs the compiler to treat the sequence of bits
        // (object representation) of <expression> as if it had the type
        // <new_type>.
        return *reinterpret_cast<const T*>(data_ + pos);
    }
private:
    typename std::aligned_storage<sizeof(T), alignof(T)>::type data_[N];
    size_t siz_{0};
};

template <typename T>
class foo {
public:
    explicit foo(T i) : i_(i) { /* nop */ }
    ~foo() = default;

    friend std::ostream&
    operator<<(std::ostream& os, const foo& f)
    {
        os << f.i_;
        return os;
    }
private:
    T i_;
};

int
main(int argc, const char *argv[])
{
    static_vector<foo<int>, 3> v;
    v.emplace_back(42);
    v.emplace_back(420);
    std::cout << v[1] << "\n";

    return 0;
}
