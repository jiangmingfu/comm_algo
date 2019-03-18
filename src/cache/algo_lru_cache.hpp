/**
 *
 * @Author jiangmingfu
 * @Date   2019.03.17
 */

#ifndef __ALGO_LRU_CACHE_HPP
#define __ALGO_LRU_CACHE_HPP

#include <functional>

namespace algo {
    template <class K, class V>
    class LRUCache {
    public:
        using ReleaseCallback = std::function<void (V& v)>();

        LRUCache(std::size_t cache_size);
        ~LRUCache();

        void SetCallback(ReleaseCallback* callback);

        void Put(const K& k, const V& v);
        bool Get(const K& k, V& v);
        void ClearAll();
        std::size_t ItemSize() const;
    };
}
#endif // __ALGO_LRU_CACHE_HPP
/* EOF */
