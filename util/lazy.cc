/**
 *  Lazy evaluation
 *  ===============
 *
 *  Use operator overloading to perform lazy evaluation.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>

class num {
public:
	num() = delete;

	num(int n)
		: n_{n}
	{
		/* nop */
	}

	~num() = default;

	friend class num_add_;

	int
	value() const
	{
		return n_;
	}
private:
	int n_;
};

class num_add_ {
public:
	num_add_() = delete;

	num_add_(const num& lhs, const num& rhs)
		: lhs_{lhs}
		, rhs_{rhs}
	{
		/* nop */
	}

	~num_add_() = default;

	operator num() const {
		return lhs_.n_ + rhs_.n_;
	}
private:
	const num& lhs_;
	const num& rhs_;
};

num_add_
operator+(num lhs, num rhs)
{
	return num_add_(lhs, rhs);
}

int
main()
{
	num a{42}, b{69};
	auto c = a + b;
	// Evaluation happens in the user-defined conversion `(num)c'.
	std::cout << ((num)c).value() << std::endl;
	return 0;
}
