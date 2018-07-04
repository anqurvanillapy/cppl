/**
 *  timsort
 *  =======
 *
 *  Very naive implementation of the *glorious* timsort, sarcasm intended.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <vector>
#include <cmath>

namespace {

template <typename T>
void
debug(const std::vector<T>& v)
{
	std::cout << "[";
	for (auto&& i : v) std::cout << i << ",";
	if (!v.empty()) std::cout << "\b";
	std::cout << "]" << std::endl;
}

template <typename T>
size_t
binsearch(const std::vector<T>& v, T val, size_t start, size_t end)
{
	if (start < end) {
		auto mid = std::round((start + end) / 2);
		if (v[mid] < val) {
			return binsearch(v, val, mid + 1, end);
		} else if (v[mid] > val) {
			return binsearch(v, val, start, mid - 1);
		} else {
			return mid;
		}
	} else if (start == end) {
		return v[start] > val ? start : start + 1;
	} else {
		return start;
	}
}

template <typename T>
auto
insertsort(std::vector<T>& v)
{
	const auto siz = v.size();
	for (size_t i = 1; i < siz; ++i) {
		auto pos = binsearch(v, v[i], 0, i - 1);
		auto item = v[i];
		v.erase(v.begin() + i);
		v.insert(v.begin() + pos, item);
	}
	return v;
}

template <typename T>
auto
merge(std::vector<T> lhs, std::vector<T> rhs)
{
	if (lhs.empty()) {
		return rhs;
	}

	if (rhs.empty()) {
		return lhs;
	}

	auto v1 = std::vector<T>();

	if (lhs[0] < rhs[0]) {
		auto v2 = merge(std::vector<T>(lhs.begin() + 1, lhs.end()), rhs);
		v1.push_back(lhs[0]);
		v1.insert(v1.end(), v2.begin(), v2.end());

		return v1;
	}

	auto v2 = merge(lhs, std::vector<T>(rhs.begin() + 1, rhs.end()));
	v1.push_back(rhs[0]);
	v1.insert(v1.end(), v2.begin(), v2.end());

	return v1;
}

} /* namespace */

template <typename T>
std::vector<T>
timsort(const std::vector<T>& v)
{
	const auto siz = v.size();
	auto unsorted_runs = std::vector<std::vector<T>>();
	auto sorted_runs = std::vector<std::vector<T>>();
	auto run = std::vector{v[0]};

	for (size_t i = 1; i < siz - 1; ++i) {
		if (v[i] < v[i - 1]) {
			if (run.empty()) {
				auto item = v[i];
				unsorted_runs.push_back(std::vector{item});
				run.push_back(item);
			} else {
				unsorted_runs.push_back(run);
				run.clear();
				run.push_back(v[i]);
			}
		} else {
			run.push_back(v[i]);
		}
	}

	run.push_back(v[siz - 1]);
	unsorted_runs.push_back(run);

	for (auto&& r : unsorted_runs) {
		sorted_runs.push_back(insertsort(r));
	}

	auto sorted = std::vector<T>();
	for (auto&& r : sorted_runs) {
		sorted = merge(sorted, r);
	}

	return sorted;
}

int
main()
{
	debug(timsort(std::vector{2, 8, 3, 1, 5, 6, 4, 7}));
	debug(timsort(std::vector{8, 7, 6, 5, 4, 3, 2, 1}));
	debug(timsort(std::vector{1, 1, 1, 1}));
	return 0;
}
