/**
 *  Vector implemented by array
 */

template <class T>
class mVector {
public:
    // Type definitions
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;

    // Constructors
    mVector() { create(); }
    explicit mVector(size_type n, const T& val = T()) { create(n, val); }

    // Getters
    size_type size() const { return limit - data; }
    T& operator[](size_type i) { return data[i]; } // efficient for big objects
    const T& operator[](size_type i) const { return data[i]; }

    // TODO: operations that return iterators
private:
    iterator data;
    iterator limit;
};
