#ifndef __ALGO_SEARCH_KTH_ELEMENT_HPP__
#define __ALGO_SEARCH_KTH_ELEMENT_HPP__

#include <stdint.h>
#include "algo_heap_sort.hpp"

namespace algo {

    // 查找第k大元素
    template <class T, class Comparator>
    bool FindElementOfKth(T d[], int32_t n, int32_t k, T& v)
    {
        if (k >= n) {
            return false;
        }

        BinaryHeap heap(k);
        heap.CreateHeap(d, k);

        for (int i = k; i < n; ++i) {
            if (d[i] > heap.Top()) {
                heap.UpdateTop(d[i]);
            }
        }

        v = *heap.Top();
        return true;
    }
}

#endif // __ALGO_SEARCH_KTH_ELEMENT_HPP__
/* EOF */
