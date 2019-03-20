/**
 *
 *  @Author jiangmingfu
 *  @Date   2019.03.20
 */

#ifndef __ALGO_MERGE_SORT_HPP__
#define __ALGO_MERGE_SORT_HPP__

#include <stdint.h>
#include "algo_allocator.h"

namespace algo {

    // 归并排序
    template <class T>
    void Merge(T* data, int32_t s1, int32_t e1, int32_t s2, int32_t e2, T* swap);

    template <class T>
    void MergeSortBySlice(T* data, int32_t s, int32_t e, T* swap);

    template <class T>
    void MergeSort(T* data, int32_t n)
    {
        T* tmp = Allocator::AllocateMultiObjs<T>(n);
        MergeSortBySlice(data, 0, n-1, tmp);
        Allocator::DeallocMultiObjs(tmp);
    }

    template <class T>
    void MergeSortBySlice(T* data, int32_t s, int32_t e, T* swap)
    {
        if (s >= e) {
            return;
        }

        int32_t mid = s + ((e - s)>>1);
        MergeSortBySlice(data, s, mid, swap);
        MergeSortBySlice(data, mid + 1, e, swap);
        Merge(data, s, mid, mid + 1, e, swap);
    }

    template <class T>
    void Merge(T* data, int32_t s1, int32_t e1, int32_t s2, int32_t e2, T* swap)
    {
        int32_t s = s1;
        int32_t k = 0;
        while(s1 <= e1 && s2 <= e2) {
            if (data[s1] <= data[s2]) {
                swap[k++] = data[s1++];
            }
            else {
                swap[k++] = data[s2++];
            }
        }

        while (s1 <= e1) {
            swap[k++] = data[s1++];
        }

        while (s2 <= e2) {
            swap[k++] = data[s2++];
        }

        for (int32_t i = 0; i < k; ++i) {
            data[s + i] = swap[i];
        }
    }
}
#endif // __ALGO_MERGE_SORT_HPP__
/* EOF */
