/**
 *
 *  @Author jiangmingfu
 *  @Date   2019.03.20
 */

#ifndef __ALGO_INSERT_SORT_HPP__
#define __ALGO_INSERT_SORT_HPP__

#include <functional>

namespace algo {
    template <class T, class Cmp = std::greater<>>
    void InsertSort(T* data, int32_t n)
    {
        int32_t j;
        T tmp;
        for (int32_t i = 1; i < n; ++i) {
            tmp = data[i];
            for (j = i - 1; j >= 0; --j) {
                if (Cmp(data[j], data[i])) {
                    data[j + 1] = data[j];
                }
                else {
                    break;
                }
            }
            data[j] = tmp;
        }
    }
}
#endif // __ALGO_INSERT_SORT_HPP__
/* EOF */
