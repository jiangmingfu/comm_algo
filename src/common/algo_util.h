/**
 *
 * @Author jiangmingfu
 * @Date   2019.03.24
 */

#ifndef __ALGO_UTIL_H__
#define __ALGO_UTIL_H__

#include <stdint.h>

namespace algo {
    class Util {
    public:
        // 计算一个整数最接近的2的n次幂
        static uint32_t RoundUpPowerOfTwo(uint32_t v);
    };
}
#endif // __ALGO_UTIL_H__
/* EOF */
