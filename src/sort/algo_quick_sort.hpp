/**
 *
 * @Author jiangmingfu
 * @Date   2019.03.24
 */

#ifndef __ALGO_QUICK_SORT_HPP__
#define __ALGO_QUICK_SORT_HPP__


#define QUICK_SORT_OPT  1 // 开启快速排序优化

#if QUICK_SORT_OPT
    #include "algo_insert_sort.hpp"
#endif

namespace algo {

    // 快速排序<优化版>
    template <class T>
    void Swap(T& a, T& b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }

    template <class T>
    int Partition(T d[], int32_t l, int32_t h)
    {
#if QUICK_SORT_OPT
        // 使用三中选一法选取分区点
        std::size_t mid = l + ((h - l) >> 1);

        if (d[mid] < d[l]) {
            Swap(d[mid], d[l]);
        }

        if (d[mid] > d[h]) {
            Swap(d[mid], d[h]);

            if (d[mid] > d[l]) {
                Swap(d[mid], d[l]);
            }
        }

        Swap(d[mid], d[h]);
#endif
        T key = d[h];
        std::size_t slow = l;
        std::size_t fast = l;

        while (fast < h) {
            if (d[fast] <= key) {
                if (fast != slow) {
                    Swap(d[fast], d[slow]);
                }
                ++slow;
            }
            ++fast;
        }

        Swap(d[slow], d[h]);
        return slow;
    }

    template <class T>
    void QuickSortBySlice(T d[], int32_t s, int32_t e)
    {
#if QUICK_SORT_OPT
        // 小量无序元素使用插入排序
        if ((e - s) + 1 <= 16) {
            InsertSort(d+s, e - s + 1);
            return;
        }
#else
        if (s >= e) {
            return;
        }
#endif

        int m = Partition(d, s, e);
        QuickSortBySlice(d, s, m-1);
        QuickSortBySlice(d, m+1, e);
    }

    template <class T>
    void QuickSort(T d[], std::size_t n)
    {
        QuickSortBySlice(d, 0, n-1);
    }
}
#endif // __ALGO_QUICK_SORT_HPP__
/* EOF */
