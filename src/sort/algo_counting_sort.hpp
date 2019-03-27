/**
 *
 * @Author jiangmingfu
 * @Date   2019.03.26
 */

#ifndef __ALGO_COUNTING_SORT_HPP__
#define __ALGO_COUNTING_SORT_HPP__

#include <stdint.h>
#include <string.h>
#include "algo_allocator.h"

namespace algo {

    bool CalcRange(int32_t d[], int32_t n, int32_t& min, int32_t& max)
    {
        if (n < 2) {
            return false;
        }

        min = d[0];
        max = d[0];

        for (int32_t i = 1; i < n; ++i) {
            if (d[i] < min) {
                min = d[i];
            }

            if (d[i] > max) {
                max = d[i];
            }
        }
        return true;
    }

    // 计数排序
    bool CountingSort(int32_t d[], int32_t n)
    {
        int32_t max = 0;
        int32_t min = 0;
        if (!CalcRange(d, n, min, max)) {
            return false;
        }

        int32_t* count_data = (int32_t*)Allocator::AllocateMem((size_t)(max - min + 1), sizeof(int32_t));

        for (int32_t i = 0; i < n; ++i) {
            count_data[d[i] - min]++;
        }

        for (int32_t i = 1; i < (max - min + 1); ++i) {
            count_data[i] += count_data[i-1];
        }

        int32_t * order_data = (int32_t*)Allocator::AllocateMem((size_t)n, sizeof(int32_t));
        for (int32_t i = n-1; i >= 0; --i) {
            order_data[count_data[d[i] - min] - 1] = d[i];
            --count_data[d[i] - min];
        }


        memcpy(d, order_data, n * sizeof(int32_t));

        Allocator::DeallocateMem(count_data);
        Allocator::DeallocateMem(order_data);
        return true;
    }
}
#endif // __ALGO_COUNTING_SORT_HPP__
/* EOF */
