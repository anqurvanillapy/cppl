/**
 *  Static/dynamic polymorphism
 *  ===========================
 *
 *  - Polymorphism achieved by:
 *      + CRTP (static)
 *      + `static` member function
 *      + `virtual` (dynamic)
 */

#include <iostream>

template <typename T>
class base {
public:
	void
	interface()
	{
		std::cout << "crtp interface called" << std::endl;
		static_cast<T*>(this)->impl();
		std::cout << "crtp interface finished" << std::endl;
	}

	static void
	static_interface()
	{
		std::cout << "static interface called" << std::endl;
		T::static_impl();
		std::cout << "static interface finished" << std::endl;
	}

	virtual void dynamic_interface() = 0;

	void
	dynamic_dosomething()
	{
		std::cout << "dynamic interface called" << std::endl;
		dynamic_interface();
		std::cout << "dynamic interface finished" << std::endl;
	}
};

class derived : public base<derived> {
public:
	void
	impl()
	{
		std::cout << "crtp impl" << std::endl;
	}

	static void
	static_impl()
	{
		std::cout << "static impl" << std::endl;
	}

	void
	dynamic_interface()
	{
		std::cout << "dynamic impl" << std::endl;
	}
};

int
main()
{
	derived wtf;
	wtf.interface();
	wtf.static_interface();
	wtf.dynamic_dosomething();
	return 0;
}
