/**
 *  mutable
 *  =======
 *
 *  `mutable' for const correctness ftw!
 */

#include <iostream>

class foo {
public:
	int
	value() const
	{
		if (!is_valid_) return b_;
		is_valid_ = true;
		return a_;
	};
private:
	int a_{42};
	int b_{69};
	mutable bool is_valid_{};
};

int
main()
{
	foo x;
	std::cout << x.value() << std::endl;
	return 0;
}
