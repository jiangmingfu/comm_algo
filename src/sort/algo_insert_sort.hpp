/**
 *
 *  @Author jiangmingfu
 *  @Date   2019.03.20
 */

#ifndef __ALGO_INSERT_SORT_HPP__
#define __ALGO_INSERT_SORT_HPP__

#include <functional>

namespace algo {
    template <class T, class Cmp = std::greater<T> >
    void InsertSort(T* data, int32_t n)
    {
        Cmp cmp;
        int32_t j = 0;
        for (int32_t i = 1; i < n; ++i) {
            T tmp = data[i];
            for (j = (int32_t)(i - 1); j >= 0; --j) {
                if (data[j] > tmp) {
                    data[j + 1] = data[j];
                }
                else {
                    break;
                }
            }
            data[j+1] = tmp;
        }
    }
}
#endif // __ALGO_INSERT_SORT_HPP__
/* EOF */
