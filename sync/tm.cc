/*
 *  Transactional memory
 *  ====================
 *
 *  A somewhat cloud cuckoo land of C++.
 *
 *  Note: Compile with -fgnu-tm.
 */

#include <vector>
#include <thread>
#include <cassert>

int i = 0;

int
main()
{
	std::vector<std::thread> v(16);

	for (auto& t : v) {
		t = std::thread([&] {
			synchronized { ++i; }
		});
	}

	for (auto& t : v) {
		t.join();
	}

	assert(i == 16);

	// Unimplemented feature on my GCC 7.2.0...

//	try {
//		atomic_cancel {
//			for (int n = 0; n < 16; ++n) ++i;
//			throw new std::runtime_error("force cancel");
//		}
//	} catch (...) {
//		/* nop */
//	}


//	assert(i == 16);

	return 0;
}
