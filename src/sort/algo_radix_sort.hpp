/**
 *
 * @Author jiangmingfu
 * @Date   2019.03.27
 */
#ifndef __ALGO_RADIX_SORT_HPP__
#define __ALGO_RADIX_SORT_HPP__

#include <stdint.h>
#include <string.h>
#include "algo_allocator.h"

namespace algo {

    int32_t CalcMaxRadixNum(uint32_t d[], int32_t n)
    {
        uint32_t max = d[0];

        for (int i = 1; i < n; ++i) {
            if (d[i] > max) {
                max = d[i];
            }
        }

        int radix_count = 0;
        while (max > 0) {
            max /= 10;
            ++radix_count;
        }
        return radix_count;
    }

    int GetLevelDigtial(uint32_t d, int level)
    {
        while (level > 0 && d > 0) {
            d /= 10;
            --level;
        }

        return d%10;
    }

    // 基数排序
    void RadixSort(uint32_t d[], int32_t n)
    {
        int32_t radix_num = CalcMaxRadixNum(d, n);

        int32_t count_ptr[10] = {0};
        uint32_t* tmp_ptr = (uint32_t*)Allocator::AllocateMem(n, sizeof(uint32_t));

        for (int i = 0; i < radix_num; ++i) {

            memset(count_ptr, 0, sizeof(count_ptr));
            for (int j = 0; j < n; ++j) {
                count_ptr[GetLevelDigtial(d[j], i)]++;
            }

            for (int k = 1; k < 10; ++k) {
                count_ptr[k] += count_ptr[k-1];
            }

            for (int j = n - 1; j >= 0; --j) {
                int m = count_ptr[GetLevelDigtial(d[j], i)];
                tmp_ptr[count_ptr[GetLevelDigtial(d[j], i)]-1] = d[j];
                count_ptr[GetLevelDigtial(d[j], i)] -= 1;
            }

            memcpy(d, tmp_ptr, n * sizeof(uint32_t));
        }

        Allocator::DeallocateMem(tmp_ptr);
    }
}
#endif // __ALGO_RADIX_SORT_HPP__
/* EOF */
