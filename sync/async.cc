/**
 *  std::async
 *  ==========
 *
 *  Note: Compile with -std=c++11 -pthread.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>

template <typename It>
int
par_sum(It begin, It end)
{
	auto len = end - begin;
	if (len < 100) {
		return std::accumulate(begin, end, 0);
	}
	It mid = begin + len / 2;
	// Asynchronously accumulates the vector.
	auto res = std::async(std::launch::async,
						  par_sum<It>, mid, end);
	int sum = par_sum(begin, mid);
	std::cout << sum << '\n';
	return sum + res.get();
}

int
main()
{
	std::vector<int> v(1000);
	std::iota(v.begin(), v.end(), 0);
	auto sum = par_sum(v.begin(), v.end());
	std::cout << "sum=" << sum << '\n';
	return 0;
}
