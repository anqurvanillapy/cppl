/**
 *  Radix sort
 *  ==========
 *
 *  Given an integer array with n elements, in which every value is in the range
 *  [0, n - 1].  How to find at least one duplicate in O(1) space and O(n) time?
 *
 *  - Radix sort
 *  - Counting occurrences
 */

#include <iostream>
#include <vector>

void
repr(std::vector<int>& v)
{
    std::cout << "{";
    for (auto r : v) std::cout << r << ", ";
    std::cout << "\b\b}" << std::endl;
}
/// get_dup and get_dup1 would modify the vector, hence they take the copy.

/* Sublinear (worst). */

int
get_dup(std::vector<int> v)
{
    unsigned i, j, siz = v.size();
    int temp;

    if (!siz) goto not_found;
    for (i = 0, j = v[i]; i < siz; j = v[i]) {
        if (i == j) { ++i; continue; }
        if (v[i] == v[j]) goto found;
        temp = v[j]; v[j] = v[i]; v[i] = temp;
    }
not_found:
    return -1;
found:
    return v[i];
}

/* theta(4n). */

int
get_dup1(std::vector<int> v)
{
    unsigned i, temp, siz = v.size();

    if (!siz) goto not_found;
    // An element can at most duplicate `siz' times, hence the multiplier.
    for (i = 0; i < siz; ++i) v[i] *= siz;
    for (i = 0; i < siz; ++i) {
        // v[v[i]/siz] might not work as expected.
        temp = v[i] / siz;
        v[temp] += 1;
    }
    for (i = 0; i < siz; ++i) v[i] %= siz;
    // repr(v);
    for (i = 0; i < siz; ++i) if (v[i] > 1) goto found;
not_found:
    return -1;
found:
    return v[i];
}

int
main(int argc, const char *argv[])
{
    std::vector<int> v{6, 5, 4, 3, 2, 2, 1};
    // std::vector<int> v{5, 4, 3, 2, 1, 0};
    std::cout << get_dup(v) << std::endl;
    std::cout << get_dup1(v) << std::endl;

    std::cout << "v="; repr(v);

    return 0;
}
