/**
 *  Vector Implemented By Array
 *  ===========================
 *
 *  A simple reference implementation from book Accelerated C++.
 */

/**
 *  ----------------------------------------------------------------------------
 *  Declarations
 *  ----------------------------------------------------------------------------
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

    // Copy control
    mVector(const mVector& v) { create(v.begin(), v.end()); }   // copy ctor
    mVector& operator=(const mVector&);                         // assignment

    // Destructors
    ~mVector() { uncreate(); }

    // Getters
    size_type size() const { return limit - data; }

    T& operator[](size_type i) { return data[i]; }  // efficient for big objects
    const T& operator[](size_type i) const { return data[i]; }

    // Operations that return iterators
    iterator begin() { return data; }
    const_iterator begin() const { return data; }

    iterator end() { return avail; }
    const_iterator end() const { return avail; }

    // Dynamic member functions
    void
    push_back(const T& val)
    {
        if (avail == limit) grow(); // get some space if needed
        unchecked_append(val);      // append the new elements
    }
private:
    iterator data;  // first element in mVector
    iterator avail; // points to the end of initialized elements
    iterator limit; // points to the end of uninitialized storage

    // Facilities for flexible memory allocation
    allocator<T> alloc; // object to handle memory allocation

    // Allocation and initialization of underlying array
    void create();
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    // Destroy the elements in the array and free the memory
    void uncreate();

    // Support functions for push_back
    void grow();
    void unchecked_append();
};

/**
 *  ----------------------------------------------------------------------------
 *  Public functions implementations
 *  ----------------------------------------------------------------------------
 */

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

/**
 *  ----------------------------------------------------------------------------
 *  Private functions implementations
 *  ----------------------------------------------------------------------------
 */

template <class T>
void
mVector<T>::create()
{
    data = avail = limit = 0;
}

template <class T>
void
mVector<T>::create(size_type n, const T& val)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    uninitialized_fill(data, limit, val);
}

template <class T>
void
mVector<T>::create(const_iterator i, const_iterator j)
{
    data = alloc.allocate(j - i);
    limit = avail = uninitialized_copy(i, j, data);
}
