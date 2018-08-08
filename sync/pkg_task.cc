/**
 *  Packaged task
 *  =============
 *
 *  Note: Compile with -std=c++11 -pthread.
 */

#include <iostream>
#include <thread>
#include <future>

int
main()
{
	std::packaged_task<int(int, int)> t1([](int a, int b) { return a + b; });
	std::packaged_task<int(int, int)> t2([](int a, int b) { return a * b; });

	std::future<int> res1 = t1.get_future();
	std::future<int> res2 = t2.get_future();

	std::thread th1(std::move(t1), 42, 69);
	std::thread th2(std::move(t2), 42, 69);

	th1.join(); th2.join();
	std::cout << res1.get() << "," << res2.get() << std::endl;

	return 0;
}
