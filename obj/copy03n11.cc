/**
 *  Copy in C++03 and C++11
 *  =======================
 *
 *  Some differences between using copy constructor/assignment operator in C++03
 *  and C++11 and their debugging hardships.
 */

class foo03 {
public:
    explicit foo03(int n) : n_(n) { /* nop */ }
    ~foo03() { /* nop */ }
private:
    foo03(const foo03&) { /* nop */ }
    foo03&
    operator=(const foo03& rhs)
    {
        n_ = rhs.n_;
        return *this;
    }

    int n_;
};

class foo11 {
public:
    explicit foo11(int n) : n_(n) { /* nop */ }
    ~foo11() { /* nop */ }

    foo11(const foo11&) = delete;
    foo11& operator=(const foo11&rhs) = delete;
private:
    int n_;
};

int
main(int argc, const char *argv[])
{
    // In C++03 we can declare the copy ctor/assign optr as private members.
    foo03 a03(42), b03(420);
    // a03 = b03;

    // In C++11 the member functions are ``deleted''.
    foo11 a11(42), b11(420);
    // a11 = b11;
    return 0;
}
