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

    // TODO: Destructors

    // Copy control
    mVector(const mVector& v) { create(v.begin(), v.end()); }   // copy ctor
    mVector& operator=(const mVector&);                         // assignment

    // Getters
    size_type size() const { return limit - data; }
    T& operator[](size_type i) { return data[i]; }  // efficient for big objects
    const T& operator[](size_type i) const { return data[i]; }

    // Operations that return iterators
    iterator begin() { return data; }
    const_iterator begin() const { return data; }

    iterator end() { return limit; }
    const_iterator end() const { return limit; }
private:
    iterator data;
    iterator limit;
};

template <class T>
mVector<T>&
mVector<T>::operator=(const mVector& rhs)   // rhs: right-hand side
{
    // Check for self-assignment    
    if (&rhs != this) {
        // Free the array in the left-hand side
        uncreate();
        // Copy elements from the right to left
        create(rhs.begin(), rhs.end());
    }

    return *this;
}
