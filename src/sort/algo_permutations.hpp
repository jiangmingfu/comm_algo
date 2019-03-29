/*
 *  @Author jiangmingfu
 *  @Date  2019.03.29
 *
 */

#ifndef __ALGO_PERMUTATIONS_HPP__
#define __ALGO_PERMUTATIONS_HPP__

#include <stdint.h>
#include <functional>

namespace algo {

    // 全排列
    template <class T>
    // n: 数组元素个数
    // k: 需要全排列的元素个数
    void CalcPermutations(T d[], int32_t n, int32_t k) {
        if (k == 1) {
            // TODO: 输出全排列
        }
        else {
            for (int32_t i = 0; i < k; ++i) {
                std::swap(d[i], d[k-1]);
                CalcPermutations(d, n, k - 1);
                std::swap(d[i], d[k-1]);
            }
        }
    }
}
#endif // __ALGO_PERMUTATIONS_HPP__
/* EOF */
