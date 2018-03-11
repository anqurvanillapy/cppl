/**
 *  my_shared_ptr
 *  =============
 *
 *  A simple implementation of non-thread-safe std::shared_ptr<T>.
 */

#include <utility>
#include <iostream>
#include <cassert>

class refcnt {
public:
	refcnt()
		: cnt_{0}
	{
		/* nop */
	}

	refcnt& operator=(const refcnt&)    = default;
	refcnt(const refcnt&)               = default;
	refcnt& operator=(refcnt&&)         = default;
	refcnt(refcnt&&)                    = default;

	~refcnt() = default;

	inline void
	inc()
	{
		++cnt_;
	}

	inline int
	dec()
	{
		return --cnt_;
	}

	inline int
	count() const
	{
		return cnt_;
	}
private:
	int cnt_;
};

template <typename T>
class my_shared_ptr {
public:
	my_shared_ptr(T* t)
		: t_{t}
		, cnt_{}
	{
		cnt_.inc();
	}

	~my_shared_ptr()
	{
		if (cnt_.dec() == 0) delete t_;
	}

	T&
	operator*() const
	{
		return *t_;
	}

	T*
	operator->() const
	{
		return t_;
	}

	my_shared_ptr<T>&
	operator=(const my_shared_ptr<T>& rhs)
	{
		t_      = rhs.t_;
		cnt_    = rhs.cnt_;
		cnt_.inc();

		return *this;
	}

	my_shared_ptr(const my_shared_ptr& rhs)
	{
		operator=(rhs);
	}

	my_shared_ptr<T>&
	operator=(my_shared_ptr<T>&& rhs)
	{
		if (this != &rhs) {
			if (cnt_.dec() == 0 && t_ != nullptr) {
				delete t_;
			}

			t_      = rhs.t_;
			cnt_    = rhs.cnt_;
			cnt_.inc();
		}

		return *this;
	}

	my_shared_ptr(my_shared_ptr&& rhs)
	{
		operator=(rhs);
	}

	inline int
	count() const
	{
		return cnt_.count();
	}
private:
	T* t_;
	refcnt cnt_;
};

class foo {
public:
	foo() = default;
	~foo()
	{
		std::cout << "foo dtor" << std::endl;
	}
};

int
main()
{
	my_shared_ptr<foo> p(new foo);
	my_shared_ptr<foo> q = p;

	assert(q.count() == 2);

	my_shared_ptr<foo> r(std::move(p));

	assert(r.count() == 2);

	{
		my_shared_ptr<foo> s = r;
		assert(s.count() == 3);
	}

	assert(r.count() == 2);

	// foo dtor runs once.
	return 0;
}
