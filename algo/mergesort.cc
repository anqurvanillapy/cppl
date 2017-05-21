/**
 *  Mergesort
 *  =========
 *
 *  Mergesort an array on the heap.
 */

#include <iostream>
#include <vector>

void
_merge(int low, int mid, int high, std::vector<int> *uv, std::vector<int> *tv)
{
    int i, j, n;

    for (i = low, j = mid + 1, n = low; i <= mid && j <= high; ++n) {
        if ((*uv)[i] <= (*uv)[j]) (*tv)[n] = (*uv)[i++];
        else (*tv)[n] = (*uv)[j++];
    }

    while (i <= mid) (*tv)[n++] = (*uv)[i++];
    while (j <= high) (*tv)[n++] = (*uv)[j++];
    for (n = low; n <= high; ++n) (*uv)[n] = (*tv)[n];
}

void
_sort(int low, int high, std::vector<int> *uv, std::vector<int> *tv)
{
    int mid;

    if (low < high) {
        mid = (low + high) / 2;
        _sort(low, mid, uv, tv);
        _sort(mid + 1, high, uv, tv);
        _merge(low, mid, high, uv, tv);
    }
}

void
mergesort(std::vector<int> *v)
{
    int low = 0;
    int high = v->size() - 1;
    std::vector<int> *tv = new std::vector<int>(v->size());

    _sort(low, high, v, tv);
    delete tv;
}

int
main(int argc, const char *argv[])
{
    std::vector<int> *v = new std::vector<int>{0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    mergesort(v);

    std::cout << "[ ";
    for (auto r : *v) std::cout << r << ", ";
    std::cout << "]" << std::endl;

    return 0;
}
