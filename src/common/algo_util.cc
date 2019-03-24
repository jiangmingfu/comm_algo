/**
 *
 * @Author jiangmingfu
 * @Date   2019.03.24
 */

#include "algo_util.h"

namespace algo {

    uint32_t Util::RoundUpPowerOfTwo(uint32_t v)
    {
        if (v & (v - 1) == 0) {
            return v;
        }

        v |= (v >> 1);
        v |= (v >> 2);
        v |= (v >> 4);
        v |= (v >> 8);
        v |= (v >> 16);

        return (v + 1);
    }
}
/* EOF */