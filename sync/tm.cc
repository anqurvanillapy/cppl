/*
 *  Transactional memory
 *  ====================
 *
 *  A somewhat cloud cuckoo land of C++.
 *
 *  1. `synchronized` blocks
 *  2. `__transaction_atomic` blocks
 *  3. `[[optimize_for_synchronized]]` attribute
 *
 *  Note: Compile with -fgnu-tm.
 */

#include <vector>
#include <thread>
#include <cassert>

int i = 0;

[[optimize_for_synchronized]] void
foo()
{
	++i;
}

int
main()
{
	std::vector<std::thread> v(64);

	for (auto& t : v) {
		t = std::thread([&] {
			synchronized { ++i; }
			// or using `__transaction_atomic'.
			// __transaction_atomic { ++i; }
		});
	}

	for (auto& t : v) {
		t.join();
	}

	assert(i == 64);

	for (auto& t : v) {
		t = std::thread(foo);
	}

	for (auto& t : v) {
		t.join();
	}

	assert(i == 128);

	// Unimplemented feature on my GCC 7.2.0...

//	try {
//		atomic_cancel {
//			for (int n = 0; n < 16; ++n) ++i;
//			throw new std::runtime_error("force cancel");
//		}
//	} catch (...) {
//		/* nop */
//	}


//	assert(i == 64);

	return 0;
}
